/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Core
*/

#include "Core.hpp"

Core &Core::getInstance()
{
    static Core instance;
    return instance;
}

bool Core::isIpValid(const std::string &ipAddress)
{
    std::regex regex("^([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\."
                     "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\."
                     "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\."
                     "([01]?\\d\\d?|2[0-4]\\d|25[0-5])$");
    return std::regex_match(ipAddress, regex);
}

void Core::initialize(int ac, char **av)
{
    ErrorHandling errorHandling(ac, av);
    std::string filepath = errorHandling.checkArgs();

    if (ac == 2) {
        // Local mode
        std::cout << "Starting local mode" << std::endl;
        _context.setState(new RayTracerStates::LocalMode());
        _context.getState()->initialize({
            {"filepath", filepath}
        });
        return;
    }

    if (ac < 3) return;

    std::string arg1 = av[1];
    std::string arg2 = av[2];

    if (arg1 == "localhost")
        arg1 = "127.0.0.1";

    if (isIpValid(arg1)) {
        // Client mode
        std::cout << "Client mode (" << arg1 << " : " << arg2 << ")" << std::endl;
        _context.setState(new RayTracerStates::ClientMode());
        _context.getState()->initialize({
            {"ipAddress", arg1},
            {"port", arg2}
        });
    } else {
        // Server mode
        std::cout << "Server mode (" << arg2 << ")" << std::endl;
        _context.setState(new RayTracerStates::ServerMode());
        _context.getState()->initialize({
            {"filepath", arg1},
            {"port", arg2}
        });
    }
}

void Core::run()
{
    _context.getState()->run();
}