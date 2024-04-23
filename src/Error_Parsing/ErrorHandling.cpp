/*
** EPITECH PROJECT, 2023
** RAYTRACER_ERRORHANDLING_CPP
** File description:
** ErrorHandling.cpp
*/

#include "ErrorHandling.hpp"
#include "Core/Parser.hpp"

void ErrorHandling::displayHelp()
{
    std::cout << "USAGE:\t./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "\tSCENE_FILE: scene configuration" << std::endl;
    std::cout << std::endl << "===============OR===============" << std::endl << std::endl;
    std::cout << "USAGE:\t./raytracer <server_ip> <server_port>" << std::endl;
    std::cout << "\tserver_ip:\tserver ip address" << std::endl;
    std::cout << "\tserver_port:\tserver port" << std::endl;
    std::cout << "\tIn that case you will use raytracer as a client" << std::endl;
    std::cout << std::endl << "===============OR===============" << std::endl << std::endl;
    std::cout << "USAGE:\t./raytracer <SCENE_FILE> <server_port>" << std::endl;
    std::cout << "\tSCENE_FILE:\tscene configuration" << std::endl;
    std::cout << "\tserver_port:\tserver port" << std::endl;
    std::cout << "\tIn that case you will use raytracer as a server" << std::endl;
}

std::string ErrorHandling::checkArgs()
{
    if (_ac < 2 || _ac > 4) {
        throw Error("Invalid number of arguments", "main.cpp", 84);
    }
    if (_ac == 2) {
        std::string firstArg = _av[1];
        if (firstArg == "-h" || firstArg == "--help") {
            displayHelp();
            throw Error("", "", 0);
        }
        Parser parser(firstArg);
        parser.parseFile();
        return firstArg;
    }
    if (_ac == 3) {
        std::string firstArg = _av[1];
        std::string secondArg = _av[2];
        if (firstArg == "-h" || firstArg == "--help") {
            displayHelp();
            throw Error("", "", 0);
        }
        if (secondArg == "-h" || secondArg == "--help") {
            displayHelp();
            throw Error("", "", 0);
        }
        return firstArg;
    }
}