/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** RendererCluster
*/

#ifndef RendererCluster_HPP
#define RendererCluster_HPP

#include <thread>
#include <vector>

#include "FrameBuffer.hpp"
#include "Renderer.hpp"
#include "Display/Display.hpp"

/**
 * @brief RendererCluster class
 */
class RendererCluster {
    public:
        /**
         * @brief Construct a new RendererCluster object
         * @param threadNumber The number of threads to use for rendering
         */
        explicit RendererCluster(size_t threadNumber = 1) : _threadNumber(threadNumber) {};
        ~RendererCluster() = default;

        /**
         * @brief Start the rendering process
         * @param bufferSize The size of the buffer to use for rendering (default: 1)
         *
         * @note The buffer size is the number of frame to render at once to avoid flickering effects
         * \important start() will throw an exception if the scene or the thread number is not set
         */
        void start(int bufferSize = -1, Display *display = nullptr);

        /**
         * @brief Get the FrameBuffer object containing the rendered image
         * @return FrameBuffer& The FrameBuffer object
         */
        FrameBuffer &getFrameBuffer();

        /**
         * @brief Set the number of threads to use for rendering
         * @param threadNumber The number of threads to use for rendering (default: 1)
         */
        void setThreadNumber(size_t threadNumber = 1);

        /**
         * @brief Set the scene to render
         * @param scene The scene to render
         */
        void setScene(Scene *scene, int xStart = -1, int xEnd = -1);

    private:
        size_t _threadNumber = std::thread::hardware_concurrency();
        Scene *_scene = nullptr;

        std::vector<Renderer *> _renderers;
        std::vector<std::thread> _threads;

        FrameBuffer _frameBuffer{0, 0};

        char _clusterStatus = 0;
};


#endif /* !RendererCluster_HPP */
