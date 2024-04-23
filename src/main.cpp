/*
** EPITECH PROJECT, 2023
** B_OOP_400_LIL_4_1_RAYTRACER_NOA_TRACHEZ_MAIN_CPP
** File description:
** main.cpp
*/

#include "main.hpp"

int main(int ac, char **av)
{
    try {
        Core::getInstance().initialize(ac, av);
        Core::getInstance().run();
    } catch (Error &e) {
        std::string what = e.what();
        if (!what.empty())
            std::cerr << e.what() << " In : " << e.where() << std::endl;
        return e.returnValue();
    }
    return 0;
}
