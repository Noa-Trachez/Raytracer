/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Ray
*/

#include "Ray.hpp"

Vector3 Ray::at(double t) const
{
    return origin + direction * t;
}
