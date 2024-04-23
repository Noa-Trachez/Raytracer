/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Server
*/

#include "Server.hpp"
#include <iostream>
#include <sys/select.h>
#include <unistd.h>

void Server::run()
{
    initialize();

    while (true) {
        // Refresh fds
        updateReadFds();
        updateWriteFds();

        select(FD_SETSIZE, &_readFds, &_writeFds, NULL, NULL);

        if (!_clustersStarted) {
            acceptClient();
            sendSharedFile();
        } else {
            receivePacket();
        }

        // Read from standard input
        if (FD_ISSET(0, &_readFds)) {
            std::string input;
            std::getline(std::cin, input);
            if (input == "start")
                startClusters();
            if (input == "quit")
                break;
        }
    }
}

/** ==================== NETWORK ==================== */

// TODO: Check socket / setsockopt / bind / listen return values
void Server::initialize()
{
    loadSharedFile();

    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(_serverSocket, (struct sockaddr *)&addr, sizeof(addr));

    int maxClient = 10;
    listen(_serverSocket, maxClient);
}

void Server::acceptClient()
{
    if (!FD_ISSET(_serverSocket, &_readFds)) return;

    int fd = accept(_serverSocket, NULL, NULL);
    std::cout << "New client connected" << std::endl;
    _clientSockets.push_back(new ClientSocket(fd));
}

void Server::updateReadFds()
{
    FD_ZERO(&_readFds);
    FD_SET(0, &_readFds);
    FD_SET(_serverSocket, &_readFds);
    for (auto clientSocket: _clientSockets)
        FD_SET(clientSocket->socket, &_readFds);
}

void Server::updateWriteFds()
{
    FD_ZERO(&_writeFds);
    for (auto clientSocket: _clientSockets)
        FD_SET(clientSocket->socket, &_writeFds);
}

/** ==================== PROCESS ==================== */

void Server::loadSharedFile()
{
    std::fstream file;
    file.open(_pathToSharedFile, std::fstream::in);
    if (!file.is_open())
        exit(84);

    std::string line;
    while (getline(file, line))
        _sharedFileContent += line + "\n";
    file.close();

    Scene *scene;
    Parser parser(_pathToSharedFile);
    scene = parser.parseFile();
    _sceneWidth = scene->imageWidth;
    _sceneHeight = scene->imageHeight;
}


void Server::sendSharedFile()
{
    for (auto clientSocket: _clientSockets) {
        if (!FD_ISSET(clientSocket->socket, &_writeFds) || clientSocket->fileSent) continue;
        usleep(1000000);
        std::cout << "Sending file to client" << std::endl;

        size_t bufferSize = _sharedFileContent.size();
        size_t command = 0;

        send(clientSocket->socket, &command, sizeof(size_t), 0);
        send(clientSocket->socket, &bufferSize, sizeof(size_t), 0);
        send(clientSocket->socket, _sharedFileContent.data(), _sharedFileContent.size(), 0);

        clientSocket->fileSent = true;
    }
}

void Server::startClusters()
{
    _clustersStarted = true;

    size_t xStart = 0;
    size_t xEnd = 0;

    for (auto clientSocket: _clientSockets) {
        xStart = xEnd;
        xEnd += _sceneWidth / _clientSockets.size();
        if (!FD_ISSET(clientSocket->socket, &_writeFds) || clientSocket->started) continue;

        clientSocket->xStart = xStart;
        clientSocket->xEnd = xEnd;

        size_t command = 1;
        send(clientSocket->socket, &command, sizeof(size_t), 0);

        send(clientSocket->socket, &xStart, sizeof(size_t), 0);
        send(clientSocket->socket, &xEnd, sizeof(size_t), 0);

        command = 2;
        send(clientSocket->socket, &command, sizeof(size_t), 0);

        clientSocket->started = true;
    }
}

void Server::receivePacket()
{
    static sf::Image *image;

    if (image == nullptr) {
        image = new sf::Image;
        image->create(_sceneWidth, _sceneHeight, sf::Color::Black);
    }

    bool allReceived = true;
    for (auto clientSocket: _clientSockets) {
        if (clientSocket->started)
            allReceived = false;
        if (!FD_ISSET(clientSocket->socket, &_readFds)) continue;

        size_t bufferSize = 0;
        recv(clientSocket->socket, &bufferSize, sizeof(size_t), 0);
        std::vector<uint8_t> buffer;
        std::cout << bufferSize << std::endl;
        buffer.resize(bufferSize + 1);
        recv(clientSocket->socket, buffer.data(), bufferSize, MSG_WAITALL);

        for (int y = _sceneHeight - 1; y >= 0; y--) {
            for (size_t x = 0; x <= _sceneWidth; x++) {
                sf::Color color(buffer[(y * _sceneWidth + x) * 3], buffer[(y * _sceneWidth + x) * 3 + 1], buffer[(y * _sceneWidth + x) * 3 + 2]);
                if (color.r == 0 && color.g == 0 && color.b == 0) continue;
                image->setPixel(x, y, color);
            }
        }
        clientSocket->started = false;
    }

    if (allReceived) {
        image->saveToFile("serverImage.png");
        exit(0);
    }
}
