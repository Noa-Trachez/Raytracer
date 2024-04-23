/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Math
*/

#include "Math.hpp"

float Math::smoothStep(float edge0, float edge1, float x)
{
    x = std::clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return x * x * (3 - 2 * x);
}

Vector3 Math::lerp(Vector3 a, Vector3 b, float f)
{
    return Vector3(a.x + f * (b.x - a.x), a.y + f * (b.y - a.y), a.z + f * (b.z - a.z));
}

float Math::randomFloat()
{
    std::random_device generator;

    std::uniform_real_distribution<float> distribution(-RAND_MAX, RAND_MAX);

    float dice_roll = distribution(generator);
    return static_cast<float>(dice_roll);
}

Vector3 Math::randomDirection()
{
    float x = Math::randomFloat();
    float y = Math::randomFloat();
    float z = Math::randomFloat();
    return Vector3(-x, y, z).normalize();
}

Vector3 Math::multiplyVectorByMatrix(const Vector3 &vector, const Matrix4 &matrix)
{
    return Vector3(
        vector.x * matrix._matrix[0][0] + vector.y * matrix._matrix[1][0] + vector.z * matrix._matrix[2][0] + matrix._matrix[3][0],
        vector.x * matrix._matrix[0][1] + vector.y * matrix._matrix[1][1] + vector.z * matrix._matrix[2][1] + matrix._matrix[3][1],
        vector.x * matrix._matrix[0][2] + vector.y * matrix._matrix[1][2] + vector.z * matrix._matrix[2][2] + matrix._matrix[3][2]
    );
}

Vector3 Math::reflect(const Vector3 &vector, const Vector3 &normal)
{
    return vector - normal * static_cast<float>(2 * (vector ^ normal));
}

Vector3 Math::randomInUnitSphere()
{
    while (true) {
        auto p = randomDirection();
        if (p.length() >= 1) continue;
        return p;
    }
}
