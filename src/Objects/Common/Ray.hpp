/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Ray
*/

#ifndef Ray_HPP
#define Ray_HPP

#include "Vector3.hpp"

class Ray {
    public:
        Ray() = default;
        Ray(Vector3 origin, Vector3 direction) : origin(origin), direction(direction) {};
        ~Ray() = default;

        Vector3 at(double t) const;

        Vector3 origin {};
        Vector3 direction {};
};


#endif /* !Ray_HPP */
