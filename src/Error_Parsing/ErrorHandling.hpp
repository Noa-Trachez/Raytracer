/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** ErrorHandling.hpp
*/

#ifndef RAYTRACER_ERRORHANDLING_HPP
#define RAYTRACER_ERRORHANDLING_HPP

#include <iostream>


class ErrorHandling {
    public:
        ErrorHandling(int ac, char **av) : _ac(ac), _av(av) {};
        std::string checkArgs();
        static void displayHelp();
    private:
        int _ac;
        char **_av;

};

class Error : public std::exception {
    public:
        Error(const std::string &message, const std::string &where, int return_value) : _message(message), _where(where), _return_value(return_value) {};

        const char *what() const noexcept override { return _message.c_str(); };

        const char *where() const noexcept { return _where.c_str(); }

        const int returnValue() const noexcept { return _return_value; }

    private:
        std::string _message;
        std::string _where;
        int _return_value;
};

#endif //RAYTRACER_ERRORHANDLING_HPP