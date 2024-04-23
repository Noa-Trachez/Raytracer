/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Sphere
*/

#ifndef Sphere_HPP
#define Sphere_HPP

#include "Object.hpp"

class Sphere : public Objects::AObject {
    public:
        Sphere() : AObject(_propertiesMethods) {};
        ~Sphere() override = default;

        bool intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const override;

        void setCenter(Vector3 center);
        void setRadius(double radius);
        void setMaterial(Material material);

    private:
        static std::unique_ptr<Objects::AObject> _factory();
        static bool _registered;

        static std::map<std::string, void (Objects::AObject::*)()> _propertiesMethods;

        Vector3 _center = Vector3(0, 0, -1);
        double _radius = 0.2;
        Material _material = Material(Vector3(0, 0, 0), Vector3(0, 0, 0), 0);
};


#endif /* !Sphere_HPP */
