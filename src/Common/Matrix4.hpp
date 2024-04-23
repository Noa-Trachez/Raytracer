/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Matrix4
*/

#ifndef Matrix4_HPP
#define Matrix4_HPP

#include "Vector3.hpp"

class Matrix4 {
    public:
        explicit Matrix4(
            float m00 = 1, float m01 = 0, float m02 = 0, float m03 = 0,
            float m10 = 0, float m11 = 1, float m12 = 0, float m13 = 0,
            float m20 = 0, float m21 = 0, float m22 = 1, float m23 = 0,
            float m30 = 0, float m31 = 0, float m32 = 0, float m33 = 1
        ) : _matrix{
            {m00, m01, m02, m03},
            {m10, m11, m12, m13},
            {m20, m21, m22, m23},
            {m30, m31, m32, m33}
        } {};
        ~Matrix4() = default;

        Matrix4 operator*(const Matrix4 &matrix) const;
        Vector3 operator*(const Vector3 &vector) const;

        static Matrix4 rotation(float theta, float phi);

        static Vector3 applyBarrelDistortion(Vector3 rayDirection, Vector3 cameraPosition, Vector3 cameraRotation);

        float _matrix[4][4];
};


#endif /* !Matrix4_HPP */
