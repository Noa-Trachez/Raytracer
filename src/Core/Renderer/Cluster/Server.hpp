/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Server
*/

#ifndef Server_HPP
#define Server_HPP

#include <string>
#include <vector>
#include <fstream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Parser.hpp"
#include "FrameBuffer.hpp"

/**
 * @brief Server class
 */
class Server {
    public:
        Server(std::string &pathToSharedFile, int port) : _pathToSharedFile(pathToSharedFile), _port(port) {};
        ~Server() = default;

        void run();

        class ClientSocket;
        void receivePacket();

private:

        /** ==================== NETWORK ==================== */
        void initialize();

        void acceptClient();

        void updateReadFds();
        void updateWriteFds();

        /** ==================== PROCESS ==================== */

        void loadSharedFile();
        void sendSharedFile();
        void startClusters();

        /** ==================== ATTRIBUTES ==================== */
        int _port;
        int _serverSocket;

        fd_set _readFds;
        fd_set _writeFds;
        std::vector<ClientSocket *> _clientSockets;

        std::string _pathToSharedFile;
        std::string _sharedFileContent;

        size_t _sceneWidth = 0;
        size_t _sceneHeight = 0;

        bool _clustersStarted = false;
};

class Server::ClientSocket {
    public:
        explicit ClientSocket(int socket) : socket(socket) {};
        ~ClientSocket() = default;

        int socket;

        size_t xStart = 0;
        size_t xEnd = 0;

        bool fileSent = false;
        bool started = false;
};


#endif /* !Server_HPP */
