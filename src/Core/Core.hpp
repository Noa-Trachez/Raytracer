/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Core
*/

#ifndef Core_HPP
#define Core_HPP

#include <iostream>
#include <regex>
#include <string>

#include "Parser.hpp"
#include "State.hpp"

/**
 * @brief Core class (singleton). Acting as the main container of the program
 */
class Core {
    public:
        static Core &getInstance();

        /**
         * @brief Set the internal context to the corresponding state
         * @param ac Argument Count
         * @param av Argument Vector
         */
        void initialize(int ac, char **av);

        /**
         * @brief Run the current state
         */
        void run();

        /**
         * @brief Check if the ip address is valid
         * @return true if the ip address is valid
         */
        static bool isIpValid(const std::string &ipAddress);

    private:
        Core() = default;

        Context _context;
};


#endif /* !Core_HPP */
