/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Plane
*/

#ifndef Plane_HPP
#define Plane_HPP

#include "Object.hpp"

class Plane : public Objects::AObject {
    public:
        Plane() : AObject(_propertiesMethods) {};
        ~Plane() override = default;

        bool intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const override;

        void setAxis(Vector3 axis);
        void setPosition(double position);
        void setMaterial(Material material);

    private:
        static std::unique_ptr<Objects::AObject> _factory();
        static bool _registered;

        static std::map<std::string, void (Objects::AObject::*)()> _propertiesMethods;

        Vector3 _axis = Vector3(0, 0, 0);
        double _position = 0;
        Material _material = Material(Vector3(0, 0, 0), Vector3(0, 0, 0), 0);

        Vector3 _pointOnPlane = Vector3(0, 0, 0);
};


#endif /* !Plane_HPP */
