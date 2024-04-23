/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cone.hpp
*/

#pragma once

#include "Object.hpp"

class Cone : public Objects::AObject {
    public:
        Cone() : AObject(_propertiesMethods) {};
        ~Cone() override = default;

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
