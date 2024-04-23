/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Client
*/

#include "Client.hpp"

#include <iostream>
#include <sys/select.h>

void Client::run()
{
    connectClient();

    while (true) {
        updateFds();

        receivePacket();

        if (_imageReady)
            sendFrame();
    }
}

/** ==================== NETWORK ==================== **/

void Client::connectClient()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_socket == -1)
        exit(84);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    addr.sin_addr.s_addr = inet_addr(_ip.c_str());

    if (connect(_socket, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        std::cout << "Failed to connect to server" << std::endl;
        exit(84);
    }
    std::cout << "Connected to server" << std::endl;
}


void Client::updateFds()
{
    FD_ZERO(&_readFds);
    FD_ZERO(&_writeFds);
    FD_SET(_socket, &_readFds);
    FD_SET(_socket, &_writeFds);
    select(FD_SETSIZE, &_readFds, &_writeFds, NULL, NULL);
}

void Client::sendFrame()
{
    if (!FD_ISSET(_socket, &_writeFds)) return;

    _rendererCluster.getFrameBuffer().saveToFile("screenshots/");
    std::vector<uint8_t> buffer = *(_rendererCluster.getFrameBuffer().getFrame());

    size_t bufferSize = buffer.size();
    std::cout << "Sending " << bufferSize << " bytes" << std::endl;
    send(_socket, &bufferSize, sizeof(size_t), 0);
    send(_socket, buffer.data(), bufferSize, 0);
    _imageReady = false;
}

/** ==================== PROCESS ==================== **/

void Client::receivePacket()
{
    if (!FD_ISSET(_socket, &_readFds)) return;

    size_t command;
    if (recv(_socket, &command, sizeof(size_t), 0) == 0) {
        std::cout << "Server disconnected" << std::endl;
        exit(0);
    }
    std::cout <<"Command "  << command << std::endl;

    if (command == 0) {
        size_t bufferSize;
        recv(_socket, &bufferSize, sizeof(size_t), 0);

        std::vector<char> buffer(bufferSize);
        recv(_socket, buffer.data(), bufferSize, MSG_WAITALL);

        Parser parser;
        parser.setBuffer(buffer);
        _scene = parser.parseFile(true);

    } else if (command == 1) {
        recv(_socket, &_xStart, sizeof(size_t), 0);
        recv(_socket, &_xEnd, sizeof(size_t), 0);
        std::cout << "Received " << _xStart << " to " << _xEnd << std::endl;
    } else if (command == 2) {
        startRendering();
    }
}

void Client::startRendering()
{
    std::cout << "Rendering..." << std::endl;
    _rendererCluster.setScene(_scene, _xStart, _xEnd);
    _rendererCluster.setThreadNumber(12);

    _rendererCluster.start(5);

    _imageReady = true;
}