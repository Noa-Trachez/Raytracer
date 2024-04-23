/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** State
*/

#include "State.hpp"

/** ==================== CONTEXT ==================== */

void Context::setState(State *state)
{
    delete this->_state;
    this->_state = state;
    this->_state->setContext(this);
}

State *Context::getState()
{
    return this->_state;
}

/** ==================== STATES ==================== */

void State::setContext(Context *context)
{
    this->_context = context;
}

/** ==================== LOCAL MODE ==================== */

void RayTracerStates::LocalMode::initialize(std::map<std::string, std::string> parameters)
{
    // Local mode
    Parser parser(parameters["filepath"]);
    _scene = parser.parseFile();

    _rendererCluster = new RendererCluster();
    _rendererCluster->setScene(_scene);
}

void RayTracerStates::LocalMode::run()
{
    Display *display = Display::getInstance();

    std::thread thread(RayTracerStates::LocalMode::threadEntrypoint, _rendererCluster, display);
    display->open(_scene->imageWidth, _scene->imageHeight);
    thread.detach();
}

void RayTracerStates::LocalMode::threadEntrypoint(RendererCluster *rendererCluster, Display *display)
{
    while (true) {
        rendererCluster->start(-1, display);
    }
}

/** ==================== CLIENT MODE ==================== */

void RayTracerStates::ClientMode::initialize(std::map<std::string, std::string> parameters)
{
    _ipAddress = parameters["ipAddress"];
    _port = std::stoi(parameters["port"]);
}

void RayTracerStates::ClientMode::run()
{
    Client client(_ipAddress, _port);
    client.run();
}

/** ==================== SERVER MODE ==================== */

void RayTracerStates::ServerMode::initialize(std::map<std::string, std::string> parameters)
{
    _filepath = parameters["filepath"];
    _port = std::stoi(parameters["port"]);
}

void RayTracerStates::ServerMode::run()
{
    Server server(_filepath, _port);
    server.run();
}
