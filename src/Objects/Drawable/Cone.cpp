/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cone.cpp
*/

#include "Cone.hpp"

bool Cone::_registered = Objects::Factory::_register("Cone", _factory);

std::unique_ptr<Objects::AObject> Cone::_factory()
{
    return std::make_unique<Cone>();
}

std::map<std::string, void (Objects::AObject::*)()> Cone::_propertiesMethods = {
        {"center",      reinterpret_cast<void (Objects::AObject::*)()>(&Cone::setCenter)},
        {"radius",      reinterpret_cast<void (Objects::AObject::*)()>(&Cone::setRadius)},
        {"material",    reinterpret_cast<void (Objects::AObject::*)()>(&Cone::setMaterial)},
        {"height",      reinterpret_cast<void (Objects::AObject::*)()>(&Cone::setHeight)}
};


bool Cone::intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const
{
    Vector3 rayToOrigin = ray.origin - _center;

    double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z - ray.direction.y * ray.direction.y;
    double b = 2 * (rayToOrigin.x * ray.direction.x + rayToOrigin.z * ray.direction.z - rayToOrigin.y * ray.direction.y);
    double c = rayToOrigin.x * rayToOrigin.x + rayToOrigin.z * rayToOrigin.z - rayToOrigin.y * rayToOrigin.y;

    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        double rootP = (-b - sqrt(discriminant)) / (2 * a);
        double rootN = (-b + sqrt(discriminant)) / (2 * a);
        double distance = std::min(rootP, rootN);

        if (distance >= 0 && distance < tMax && distance > tMin) {
            record.intersect = true;
            record.t = distance;
            record.point = ray.at(distance);
            record.normal = (record.point - _center).normalize();
            record.material = _material;
            return true;
        }
    }
    return false;
}

void Cone::setCenter(Vector3 center)
{
    _center = center;
}

void Cone::setRadius(double radius)
{
    _radius = radius;
}

void Cone::setMaterial(Material material)
{
    _material = material;
}

void Cone::setHeight(double height)
{
    _height = height;
}