/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Material
*/

#ifndef Material_HPP
#define Material_HPP

#include "Vector3.hpp"

/**
 * @brief Material class used to describe the material of an object
 */
class Material {
    public:
        explicit Material(
            Vector3 color = Vector3(0, 0, 0),
            Vector3 emissionColor = Vector3(1, 1, 1),
            float emissionStrength = 0.0f,
            float albedo = 0.18f,
            float reflectivity = 0.0f,
            float refractionIndex = 0.0f
        ) : color(color.toColor()),
            emissionColor(emissionColor.toColor()),
            emissionStrength(emissionStrength),
            albedo(albedo),
            reflectivity(reflectivity),
            refractionIndex(refractionIndex)
            {};
        ~Material() = default;

        /**
         * @brief Color of the material (0.0f = black, 1.0f = white)
         */
        Vector3 color;

        /**
         * @brief Color of the emission of the material (0.0f = black, 1.0f = white)
         * @note The emission strength is used to multiply the emission color when calculating the ray color
         */
        Vector3 emissionColor;

        /**
         * @brief Strength of the emission of the material (0.0f = no emission, +inf = full emission)
         */
        float emissionStrength;

        /**
         * @brief Absorption rate of the material (0.0f = full absorption, 1.0f = no absorption)
         * @note Default: 0.18f
         */
        float albedo;

        /**
         * @brief Is a material reflective (0.0f = no reflection, 0.01f = full reflection, >0.01f = defuse increase)
         */
        float reflectivity;

        /**
         * @brief Refraction index of the material (0.0f = no refraction, >0.0f = refraction)
         */
        float refractionIndex;
};


#endif /* !Material_HPP */
