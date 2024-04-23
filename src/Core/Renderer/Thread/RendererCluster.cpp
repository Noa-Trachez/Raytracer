/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** RendererCluster
*/

#include "RendererCluster.hpp"

void RendererCluster::start(int bufferSize, Display *display)
{
    //TODO: Clement check moi ça
    if (_clusterStatus == 0x2)
        _clusterStatus = 0x3;

    if (_clusterStatus != 0x3)
        throw std::runtime_error("RendererCluster::start: RendererCluster is not ready");

    // Create the renderers
    for (size_t i = 0; i < _threadNumber; i++)
        _renderers.push_back(new Renderer(_scene));

    FrameBuffer::Frame &frame = _frameBuffer.getFrame();

    while (bufferSize == -1 || bufferSize--) {
        // Render the scene in slices with threads
        size_t step = _scene->imageWidth / _threadNumber;
        size_t start = 0;
        if (_scene->_xStart != -1) {
            step = (_scene->_xEnd - _scene->_xStart) / _threadNumber;
            start = _scene->_xStart;
        }

        for (size_t i = 0; i < _threadNumber; i++) {
            size_t end = i == _threadNumber - 1 && _scene->_xEnd != -1 ? _scene->_xEnd : start + step;
            _threads.emplace_back(&Renderer::renderSceneSlice, _renderers[i], start, end, frame);
            start += step;
        }

        // Wait for the threads to finish and clear them
        for (size_t i = 0; i < _threadNumber; i++)
            _threads[i].join();
        _threads.clear();

        _frameBuffer.flatten();
        if (display)
            display->setImage(_frameBuffer.toImage());
        std::cout << "Buffer rendered" << std::endl;
    }

    _renderers.clear();
}

FrameBuffer &RendererCluster::getFrameBuffer()
{
    return _frameBuffer;
}

void RendererCluster::setThreadNumber(size_t threadNumber)
{
    _threadNumber = threadNumber;
    _clusterStatus |= 0x1;
}

void RendererCluster::setScene(Scene *scene, int xStart, int xEnd)
{
    _scene = scene;
    _scene->_xStart = xStart;
    _scene->_xEnd = xEnd;

    _frameBuffer = FrameBuffer(_scene->imageWidth, _scene->imageHeight);
    _clusterStatus |= 0x2;
}
