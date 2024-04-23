/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** FrameBuffer
*/

#include "FrameBuffer.hpp"
#include "Display/Display.hpp"

FrameBuffer::FrameBuffer(size_t width, size_t height) : _width(width), _height(height)
{
    size_t size = width * height * 3 + 1;

    _frame = std::make_shared<std::vector<uint8_t>>(size);
    _oldFrame = std::make_shared<std::vector<uint8_t>>(size);

    _frame->clear();
    _frame->assign(size, 0);
    _oldFrame->clear();
}

FrameBuffer::Frame &FrameBuffer::getFrame()
{
    return _frame;
}

void FrameBuffer::flatten()
{
    if (_oldFrame->empty()) {
        _oldFrame->assign(_frame->begin(), _frame->end());
        _frameCount++;
        return;
    }

    for (size_t i = 0; i < _width * _height; i++) {
        uint8_t oldR = _oldFrame->at(i * 3);
        uint8_t oldG = _oldFrame->at(i * 3 + 1);
        uint8_t oldB = _oldFrame->at(i * 3 + 2);

        uint8_t currR = _frame->at(i * 3);
        uint8_t currG = _frame->at(i * 3 + 1);
        uint8_t currB = _frame->at(i * 3 + 2);

        if (oldR != 0 || oldG != 0 || oldB != 0) {
            // Weight of the new pixel color
            float weight = 1.0f / static_cast<float>(_frameCount + 1);

            // Accumulate the color and clamp it between 0 and 255
            _frame->at(i * 3) = std::min(std::max(static_cast<uint8_t>((oldR * (1 - weight)) + (currR * weight)), 0_uchar), 255_uchar);
            _frame->at(i * 3 + 1) = std::min(std::max(static_cast<uint8_t>((oldG * (1 - weight)) + (currG * weight)), 0_uchar), 255_uchar);
            _frame->at(i * 3 + 2) = std::min(std::max(static_cast<uint8_t>((oldB * (1 - weight)) + (currB * weight)), 0_uchar), 255_uchar);
        }

        // Save the current pixel color
        _oldFrame->at(i * 3) = _frame->at(i * 3);
        _oldFrame->at(i * 3 + 1) = _frame->at(i * 3 + 1);
        _oldFrame->at(i * 3 + 2) = _frame->at(i * 3 + 2);
    }
    _frameCount++;
}

sf::Image FrameBuffer::toImage()
{
    sf::Image image;
    image.create(_width, _height);

    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            image.setPixel(x, y, sf::Color(_frame->at((x + y * _width) * 3), _frame->at((x + y * _width) * 3 + 1), _frame->at((x + y * _width) * 3 + 2)));
        }
    }
    return image;
}

void FrameBuffer::saveToFile(const std::string &path)
{
    int random = static_cast<int>(std::abs(Math::randomFloat() * 10000));
    std::string name = path + std::to_string(random) + ".png";

    sf::Image image = toImage();

    image.saveToFile(name);

    std::cout << "Image saved to " << name << std::endl;
}
