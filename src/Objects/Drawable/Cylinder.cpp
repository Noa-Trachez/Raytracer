/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

bool Cylinder::_registered = Objects::Factory::_register("Cylinder", _factory);

std::unique_ptr<Objects::AObject> Cylinder::_factory()
{
    return std::make_unique<Cylinder>();
}

std::map<std::string, void (Objects::AObject::*)()> Cylinder::_propertiesMethods = {
    {"center",      reinterpret_cast<void (Objects::AObject::*)()>(&Cylinder::setCenter)},
    {"direction",   reinterpret_cast<void (Objects::AObject::*)()>(&Cylinder::setDirection)},
    {"radius",      reinterpret_cast<void (Objects::AObject::*)()>(&Cylinder::setRadius)},
    {"material",    reinterpret_cast<void (Objects::AObject::*)()>(&Cylinder::setMaterial)}
};

bool Cylinder::intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const
{
    Vector3 axis = _direction.normalize();

    Vector3 rayToStart = ray.origin - _center;
    double a = ray.direction.dot(ray.direction) - pow(ray.direction.dot(axis), 2);
    double b = 2 * (ray.direction.dot(rayToStart) - ray.direction.dot(axis) * rayToStart.dot(axis));
    double c = rayToStart.dot(rayToStart) - pow(rayToStart.dot(axis), 2) - pow(_radius, 2);

    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        double root1 = (-b - sqrt(discriminant)) / (2 * a);
        double root2 = (-b + sqrt(discriminant)) / (2 * a);

        double t = -1.0;
        if (root1 >= tMin && root1 <= tMax)
            t = root1;
        else if (root2 >= tMin && root2 <= tMax)
            t = root2;

        if (t >= 0) {
            Vector3 intersectionPoint = ray.at(t);
            Vector3 directionToPoint = intersectionPoint - _center;
            double projection = directionToPoint.dot(axis);
            Vector3 normal = (directionToPoint - axis * static_cast<float>(projection)).normalize();

            record.intersect = true;
            record.t = t;
            record.point = intersectionPoint;
            record.normal = normal;
            record.material = _material;
            return true;
        }
    }

    return false;
}

void Cylinder::setCenter(Vector3 center)
{
    _center = center;
}

void Cylinder::setDirection(Vector3 direction)
{
    _direction = direction;
}

void Cylinder::setRadius(double radius)
{
    _radius = radius;
}

void Cylinder::setMaterial(Material material)
{
    _material = material;
}
