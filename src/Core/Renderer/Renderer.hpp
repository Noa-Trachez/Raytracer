/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Renderer
*/

#ifndef Renderer_HPP
#define Renderer_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <cmath>

#include "Common.hpp"
#include "Object.hpp"
#include "Parser.hpp"

/**
 * @brief Renderer class
 */
class Renderer {
    public:
        Renderer() = default;
        explicit Renderer(Scene *scene) : _scene(scene) {};
        ~Renderer() = default;

        /**
         * @brief Set the scene of the renderer
         * @param scene Scene to render once set
         */
        void setScene(Scene *scene);

        /**
         * @brief Render the entire scene
         */
        void renderScene();

        /**
         * @brief Render a part of the scene
         * @param xStart The position of the first column of pixels to render
         * @param xEnd The position of the last column of pixels to render
         */
        void renderSceneSlice(int xStart, int xEnd, const std::shared_ptr<std::vector<uint8_t>> &pixels);

    private:
        /**
         * @brief Render a pixel at the given position
         * @param x The x position of the pixel
         * @param y The y position of the pixel
         */
        void renderPixel(int x, int y);

        /** ====================  RAYTRACING  ==================== */

        /**
         * @brief Trace a ray and return the color of the object.
         * @param ray The ray to trace
         * @param objects The objects to trace the ray against
         * @return The color of the object the ray hit
         */
        Vector3 trace(Ray &ray, std::vector<std::unique_ptr<Objects::AObject>> &objects, size_t depth = 0);

        /**
         * @brief Check if a ray intersect with an object
         * @return true if the ray intersect with an object
         */
        static bool rayIntersect(Ray &ray, std::vector<std::unique_ptr<Objects::AObject>> &objects, Objects::IntersectionRecord &record);

        /**
         * @brief Calculate the color of the pixel using the Ambient Light
         * @param pixelColor Current color of the pixel
         * @param record Intersection record of the object
         */
        void RTAmbientLight(Vector3 &pixelColor, Objects::IntersectionRecord &record);

        /**
         * @brief Calculate the color of the pixel using the Directional Light
         * @param pixelColor Current color of the pixel
         * @param record Intersection record of the object
         */
        void RTDirectionalLight(Vector3 &pixelColor, Objects::IntersectionRecord &record);

        /**
         * @brief Calculate the color of the pixel using the Ray Casting
         * @param pixelColor Current color of the pixel
         * @param record Intersection record of the object
         */
        static void RTRayCasting(Vector3 &pixelColor, Vector3 &rayColor, Objects::IntersectionRecord &record);

        /**
         * @brief Calculate the color of the pixel using the Environment Light
         * @param pixelColor Current color of the pixel
         * @param record Intersection record of the object
         */
        static void RTEnvironmentLight(Vector3 &pixelColor, Vector3 &rayColor, Ray &ray);

        /**
         * @brief Calculate the color of the pixel using the Reflection
         * @param ray Current ray
         * @param record Intersection record of the object
         * @param scattered Scattered ray (reflected ray)
         * @return true if the ray is reflected by an object
         */
        static bool RTReflection(Ray &ray, Objects::IntersectionRecord &record, Ray &scattered);

        /**
         * @brief Calculate the color of the pixel using the Refraction
         * @param ray Current ray
         * @param record Intersection record of the object
         * @param refracted Refracted ray
         * @return true if the ray is refracted by an object
         */
        static bool RTRefraction(Ray &ray, Objects::IntersectionRecord &record, Ray &refracted);

        Scene *_scene{};
        Vector3 _currentPixelColor{};

        sf::Image _frame{};
};


#endif /* !Renderer_HPP */
