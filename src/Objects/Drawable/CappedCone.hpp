/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** CappedCone.hpp
*/

#pragma once

#include "Object.hpp"

class CappedCone : public Objects::AObject {
    public:
        CappedCone() : AObject(_propertiesMethods) {};
        ~CappedCone() override = default;

        bool intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const override;

        void setCenter(Vector3 center);
        void setRadius(double radius);
        void setMaterial(Material material);
        void setHeight(double height);


    private:
        static std::unique_ptr<Objects::AObject> _factory();
        static bool _registered;

        static std::map<std::string, void (Objects::AObject::*)()> _propertiesMethods;

        Vector3 _center;
        double _radius;
        Material _material;
        double _height;
};
