/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Display
*/

#include "Display.hpp"

Display *Display::getInstance()
{
    static Display instance;
    return &instance;
}

void Display::open(size_t width, size_t height)
{
    _width = width;
    _height = height;
    sf::Event event{};

    _window.create(sf::VideoMode(_width, _height), "Raytracer");
    _window.setPosition(sf::Vector2i(0, 0));

    while (_window.isOpen()) {
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    _window.close();
                if (event.key.code == sf::Keyboard::S) {
                    sf::Image screenshot = _frameTexture.copyToImage();
                    screenshot.saveToFile("screenshot.png");
                }
                if (event.key.code == sf::Keyboard::R) {
                    //TODO: RELOADING
                }
            }
        }
        _window.clear();
        _window.draw(_frame);
        _window.display();
    }
}

void Display::setImage(const sf::Image &image)
{
    _frameTexture.loadFromImage(image);

    _frame.setTexture(_frameTexture, true);
}
