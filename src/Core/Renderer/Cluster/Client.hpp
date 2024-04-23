/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Client
*/

#ifndef Client_HPP
#define Client_HPP

#include <string>
#include <vector>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Parser.hpp"
#include "RendererCluster.hpp"
#include "Scene.hpp"

/**
 * @brief Client class
 */
class Client {
    public:
        Client(std::string &ip, int port) : _ip(ip), _port(port) {};
        ~Client() = default;

        void run();

    private:
        /** ==================== NETWORK ==================== */
        void connectClient();

        void updateFds();

        void sendFrame();

        /** ==================== PROCESS ==================== */
        void receivePacket();

        void startRendering();
        /** ==================== ATTRIBUTES ==================== */
        std::string _ip;
        int _port;
        int _socket;
        fd_set _readFds;
        fd_set _writeFds;

        Scene *_scene;
        size_t _xStart = 0;
        size_t _xEnd = 0;

        bool _imageReady = false;

        RendererCluster _rendererCluster;
};


#endif /* !Client_HPP */
