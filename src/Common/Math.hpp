/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Math
*/

#ifndef Math_HPP
#define Math_HPP

#include <algorithm>
#include <random>

#include <cmath>

#include "Matrix4.hpp"
#include "Vector3.hpp"

#define DEG_TO_RAD 0.01745329251994329576923690768489f
#define EPSILON 0.0001f

/**
 * @brief Math class
 */
class Math {
    public:
        static float smoothStep(float edge0, float edge1, float x);

        /**
         * @brief Linear interpolation between two vectors
         * @return Interpolated vector between a and b with factor f
         */
        static Vector3 lerp(Vector3 a, Vector3 b, float f);

        /**
         * @brief Generate a random float with the random device engine
         * @return  A random float between 0 and 1
         */
        static float randomFloat();

        /**
         * @brief Generate a random direction vector
         * @note This fonction uses the randomFloat() function
         * @return A random direction vector normalized as a unit vector
         */
        static Vector3 randomDirection();

        static Vector3 multiplyVectorByMatrix(const Vector3 &vector, const Matrix4 &matrix);

        static Vector3 reflect(const Vector3 &vector, const Vector3 &normal);

        static Vector3 randomInUnitSphere();
};


#endif /* !Math_HPP */
