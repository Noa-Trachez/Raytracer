/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Vector3
*/

#include "Vector3.hpp"

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Vector3 &Vector3::operator+=(const Vector3 &vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

Vector3 &Vector3::operator*=(const Vector3 &vector)
{
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;
    return *this;
}

Vector3 &Vector3::operator*=(float number)
{
    x *= number;
    y *= number;
    z *= number;
    return *this;
}

Vector3 &Vector3::operator/=(float number)
{
    x /= number;
    y /= number;
    z /= number;
    return *this;
}

Vector3 Vector3::operator+(const Vector3 &vector) const
{
    return Vector3(
    x + vector.x,
    y + vector.y,
    z + vector.z
    );
}

Vector3 Vector3::operator-(const Vector3 &vector) const
{
    return Vector3(
    x - vector.x,
    y - vector.y,
    z - vector.z
    );
}

Vector3 Vector3::operator*(const Vector3 &vector) const
{
    return Vector3(
    x * vector.x,
    y * vector.y,
    z * vector.z
    );
}

double Vector3::dot(const Vector3 &vector) const
{
    return x * vector.x + y * vector.y + z * vector.z;
}

Vector3 Vector3::cross(const Vector3 &vector) const
{
    return Vector3(
        y * vector.z - z * vector.y,
        z * vector.x - x * vector.z,
        x * vector.y - y * vector.x
    );
}

double Vector3::operator^(const Vector3 &vector) const
{
    return x * vector.x + y * vector.y + z * vector.z;
}

Vector3 Vector3::operator+(float number) const
{
    return Vector3(
    static_cast<float>(x + number),
    static_cast<float>(y + number),
    static_cast<float>(z + number)
    );
}

Vector3 Vector3::operator*(float number) const
{
    return Vector3(
    static_cast<float>(x * number),
    static_cast<float>(y * number),
    static_cast<float>(z * number)
    );
}

Vector3 Vector3::operator/(float number) const
{
    return Vector3(
    static_cast<float>(x / number),
    static_cast<float>(y / number),
    static_cast<float>(z / number)
    );
}

double Vector3::dot(float number) const
{
    return x * number + y * number + z * number;
}

double Vector3::operator^(float number) const
{
    return x * number + y * number + z * number;
}

void Vector3::rotationX(float r)
{
    float cosR = std::cos(r);
    float sinR = std::sin(r);
    y = y * cosR - z * sinR;
    z = y * sinR + z * cosR;
}

void Vector3::rotationY(float r)
{
    float cosR = std::cos(r);
    float sinR = std::sin(r);
    x = x * cosR + z * sinR;
    z = -x * sinR + z * cosR;
}

float &Vector3::operator[](int index)
{
    if (index == 0)
        return x;
    if (index == 1)
        return y;
    if (index == 2)
        return z;
    return x;
}

double Vector3::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalize() const
{
    double currentLength = length();
    if (currentLength == 0)
        return Vector3(0, 0, 0);
    return *this / static_cast<float>(currentLength);
}

Vector3 Vector3::toColor()
{
    x = x > 255 ? 1 : x < 0 ? 0 : x > 1 ? x / 255 : x;
    y = y > 255 ? 1 : y < 0 ? 0 : y > 1 ? y / 255 : y;
    z = z > 255 ? 1 : z < 0 ? 0 : z > 1 ? z / 255 : z;
    return *this;
}

Vector3 Vector3::clamp(float min, float max)
{
    x = std::min(std::max(x, min), max);
    y = std::min(std::max(y, min), max);
    z = std::min(std::max(z, min), max);
    return *this;
}
