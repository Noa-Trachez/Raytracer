/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Matrix4
*/

#include "Matrix4.hpp"

Matrix4 Matrix4::operator*(const Matrix4 &matrix) const
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
        for (int k = 0; k < 4; k++)
            for (int j = 0; j < 4; j++)
                result._matrix[i][j] += _matrix[i][k] * matrix._matrix[k][j];
    return result;
}

Matrix4 Matrix4::rotation(float theta, float phi)
{
    Matrix4 rotationX(1, 0, 0, 0, 0, cosf(theta), -sinf(theta), 0, 0, sinf(theta), cosf(theta), 0);
    Matrix4 rotationY(cosf(phi), 0, sinf(phi), 0, 1, 0, 0, -sinf(phi), 0, cosf(phi), 0);
    return rotationX * rotationY;
}

Vector3 Matrix4::operator*(const Vector3 &vector) const
{
    Vector3 result;
    result.x = _matrix[0][0] * vector.x + _matrix[0][1] * vector.y + _matrix[0][2] * vector.z + _matrix[0][3];
    result.y = _matrix[1][0] * vector.x + _matrix[1][1] * vector.y + _matrix[1][2] * vector.z + _matrix[1][3];
    result.z = _matrix[2][0] * vector.x + _matrix[2][1] * vector.y + _matrix[2][2] * vector.z + _matrix[2][3];
    return result;
}

Vector3 Matrix4::applyBarrelDistortion(Vector3 rayDirection, Vector3 cameraPosition, Vector3 cameraRotation)
{
    Matrix4 rotationX(
        1, 0, 0, 0,
        0, cosf(cameraRotation.x), sinf(cameraRotation.x), 0,
        0, -sinf(cameraRotation.x), cosf(cameraRotation.x), 0,
        0, 0, 0, 1
    );
    Matrix4 rotationY(
        cosf(cameraRotation.y), 0, -sinf(cameraRotation.y), 0,
        0, 1, 0, 0,
        sinf(cameraRotation.y), 0, cosf(cameraRotation.y), 0,
        0, 0, 0, 1
    );
    Matrix4 rotationZ(
        cosf(cameraRotation.z), sinf(cameraRotation.z), 0, 0,
        -sinf(cameraRotation.z), cosf(cameraRotation.z), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
    Matrix4 translateN(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        -cameraPosition.x, -cameraPosition.y, -cameraPosition.z, 1
    );
    Matrix4 translateP(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        cameraPosition.x, cameraPosition.y, cameraPosition.z, 1
    );

    return rotationZ * rotationY * rotationX * translateP * translateN * rayDirection;
}
