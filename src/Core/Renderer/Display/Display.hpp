/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Display
*/

#ifndef Display_HPP
#define Display_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Display {
    public:
        static Display *getInstance();
        ~Display() = default;

        void open(size_t width, size_t height);

        void setImage(const sf::Image &image);

    private:
        Display() = default;

        size_t _width = 0;
        size_t _height = 0;

        sf::RenderWindow _window{};
        // EVENT ?

        sf::Texture _frameTexture{};
        sf::Sprite _frame{};
};


#endif /* !Display_HPP */
