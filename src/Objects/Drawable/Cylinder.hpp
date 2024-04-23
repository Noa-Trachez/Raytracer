/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cylinder
*/

#ifndef Cylinder_HPP
#define Cylinder_HPP

#include "Object.hpp"

class Cylinder : public Objects::AObject {
    public:
        Cylinder() : AObject(_propertiesMethods) {};
        ~Cylinder() override = default;

        bool intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const override;

        void setCenter(Vector3 center);
        void setDirection(Vector3 direction);
        void setRadius(double radius);
        void setMaterial(Material material);

    private:
        static std::unique_ptr<Objects::AObject> _factory();
        static bool _registered;

        static std::map<std::string, void (Objects::AObject::*)()> _propertiesMethods;

        Vector3 _center = Vector3(0, 0, 0);
        Vector3 _direction = Vector3(0, 0, 0);
        double _radius = 0.2;
        Material _material = Material(Vector3(0, 0, 0), Vector3(0, 0, 0), 0);
};


#endif /* !Cylinder_HPP */
