/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** FrameBuffer
*/

#ifndef FrameBuffer_HPP
#define FrameBuffer_HPP

#include "SFML/Graphics.hpp"

#include <memory>
#include <vector>

#include "Math.hpp"

/**
 * @brief FrameBuffer class
 * @details This class is used to store the rendered pixels of a scene
 */
class FrameBuffer {
    public:
        /**
         * @brief Construct a new FrameBuffer object
         * @param width The width of the frame to render
         * @param height The height of the frame to render
         */
        FrameBuffer(size_t width, size_t height);
        ~FrameBuffer() = default;

        using Frame = std::shared_ptr<std::vector<uint8_t>>;

        /**
         * @brief Get the internal frame
         * @return The internal frame
         */
        Frame &getFrame();

        /**
         * @brief Flatten the old frame into the new one to make the frame smoother
         */
        void flatten();

        /**
         * @brief Convert the frame (vector of uint8_t) to an image
         * @return The image
         */
        sf::Image toImage();

        /**
         * @brief Save the frame to a file
         * @param path The path to the file
         */
        void saveToFile(const std::string &path);

    private:
        size_t _width;
        size_t _height;

        Frame _frame;
        Frame _oldFrame;

        size_t _frameCount = 0;
};

/**
 * @brief Operator used to specify a literal number type.<br/>
 * Example: 255_uchar is equivalent to static_cast<unsigned char>(255)
 * @param n The literal number
 * @return Literal number as an unsigned char
 */
inline constexpr unsigned char operator "" _uchar(unsigned long long n) noexcept
{
    return static_cast<unsigned char>(n);
}


#endif /* !FrameBuffer_HPP */
