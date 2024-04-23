/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

bool Sphere::_registered = Objects::Factory::_register("Sphere", _factory);

std::unique_ptr<Objects::AObject> Sphere::_factory()
{
    return std::make_unique<Sphere>();
}

std::map<std::string, void (Objects::AObject::*)()> Sphere::_propertiesMethods = {
    {"center",      reinterpret_cast<void (Objects::AObject::*)()>(&Sphere::setCenter)},
    {"radius",      reinterpret_cast<void (Objects::AObject::*)()>(&Sphere::setRadius)},
    {"material",    reinterpret_cast<void (Objects::AObject::*)()>(&Sphere::setMaterial)}
};

bool Sphere::intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const
{
    Vector3 rayToOrigin = ray.origin - _center;

    const double a = ray.direction ^ ray.direction;
    const double b = 2 * (rayToOrigin ^ ray.direction);
    const double c = (rayToOrigin ^ rayToOrigin) - _radius * _radius;

    const double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        const double rootP = (-b - sqrt(discriminant)) / (2 * a);
        const double rootN = (-b + sqrt(discriminant)) / (2 * a);
        const double distance = std::min(rootP, rootN);

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

void Sphere::setCenter(Vector3 center)
{
    _center = center;
}

void Sphere::setRadius(double radius)
{
    _radius = radius;
}

void Sphere::setMaterial(Material material)
{
    _material = material;
}
