/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Vector3
*/

#ifndef Vector3_HPP
#define Vector3_HPP

#include <algorithm>
#include <iostream>

#include <cmath>

class Vector3 {
    public:
        explicit Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {};
        ~Vector3() = default;

        friend std::ostream &operator<<(std::ostream &out, const Vector3 &vector)
        {
            return out << vector.x << ' ' << vector.y << ' ' << vector.z;
        }

        Vector3 operator-() const; // Vector negation
        Vector3 &operator=(const Vector3 &vector) = default; // Vector assignment
        Vector3 &operator+=(const Vector3 &vector); // Vector self addition
        Vector3 &operator*=(const Vector3 &vector); // Vector self multiplication

        Vector3 &operator*=(float number); // Vector self multiplication
        Vector3 &operator/=(float number); // Vector self division

        Vector3 operator+(const Vector3 &vector) const; // Vector addition
        Vector3 operator-(const Vector3 &vector) const; // Vector subtraction
        Vector3 operator*(const Vector3 &vector) const; // Vector multiplication
        double dot(const Vector3 &vector) const; // Vector dot product
        Vector3 cross(const Vector3 &vector) const; // Vector cross product
        double operator^(const Vector3 &vector) const; // Vector scalar product

        Vector3 operator+(float number) const; // Vector addition with a number
        Vector3 operator*(float number) const; // Vector multiplication with a number
        Vector3 operator/(float number) const; // Vector division with a number
        double dot(float number) const; // Vector dot product with a number
        double operator^(float number) const; // Vector scalar product with a number

        void rotationX(float r);

        void rotationY(float r);

        float &operator[](int index); // Get the value at index

        /**
         * @brief Get the length of the vector
         * length = sqrt(x^2 + y^2 + z^2)
         * @return The length of the vector as a double
         */
        double length() const;

        /**
         * @brief Get the normalized vector
         * normalized vector = vector / length
         * @return The normalized vector scaled to a length of 1
         */
        Vector3 normalize() const;

        /**
         * @brief Set the vector as a color
         */
        Vector3 toColor();

        /**
         * @brief Clamp every component of the vector between min and max
         * @param min
         * @param max
         * @return Clamped vector
         */
        Vector3 clamp(float min, float max);

        float x;
        float y;
        float z;
};


#endif /* !Vector3_HPP */
