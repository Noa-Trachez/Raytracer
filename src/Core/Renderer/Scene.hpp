/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Scene
*/

#ifndef Scene_HPP
#define Scene_HPP

#include "Math.hpp"
#include "Object.hpp"

/**
 * @brief Class that contains all the objects and configuration of the scene
 */
class Scene {
    public:
        Scene() = default;
        ~Scene() = default;

        void setObjectList(std::vector<std::unique_ptr<Objects::AObject>> &objectList);
        void setDirectionalLight(std::vector<std::unique_ptr<Objects::AObject>> &directionalLight);
        void update();

        std::vector<std::unique_ptr<Objects::AObject>> _objects{};

        // Image
        int imageWidth = 800;
        int imageHeight = 800;
        double fieldOfView = 90;
        double aspectRatio = static_cast<double>(imageWidth) / static_cast<double>(imageHeight);

        int _xStart = -1;
        int _xEnd = -1;

        // Clipping Planes
        const double nearClippingPlane = 1.0;
        const double farClippingPlane = 100.0;

        // Viewport
        double viewportHeight = nearClippingPlane * std::tan(fieldOfView * 0.5f * DEG_TO_RAD) * 2;
        double viewportWidth = viewportHeight * aspectRatio;
        Vector3 localBottomLeftCorner = Vector3(static_cast<float>(-viewportWidth) / 2, static_cast<float>(-viewportHeight) / 2, static_cast<float>(-nearClippingPlane));

        // Camera
        Vector3 cameraPosition = Vector3(0, 0, 0);
        Vector3 cameraDirection = Vector3(0, 0, 1);
        Vector3 horizontal = Vector3(static_cast<float>(viewportWidth), 0, 0);
        Vector3 vertical = Vector3(0, static_cast<float>(-viewportHeight), 0);

        // Scene
        unsigned int rayPerPixel = 1;
        bool progressiveRendering = true;
        unsigned int maxDepth = 1;
        bool environment = false;

        // Light
        Vector3 ambientLight = Vector3(0.0f, 0.0f, 0.0f);
        std::vector<std::unique_ptr<Objects::AObject>> _directionalLight;
};


#endif /* !Scene_HPP */
