/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** CappedCone.cpp
*/

#include "CappedCone.hpp"

bool CappedCone::_registered = Objects::Factory::_register("CappedCone", _factory);

std::unique_ptr<Objects::AObject> CappedCone::_factory()
{
    return std::make_unique<CappedCone>();
}

std::map<std::string, void (Objects::AObject::*)()> CappedCone::_propertiesMethods = {
        {"center",      reinterpret_cast<void (Objects::AObject::*)()>(&CappedCone::setCenter)},
        {"radius",      reinterpret_cast<void (Objects::AObject::*)()>(&CappedCone::setRadius)},
        {"material",    reinterpret_cast<void (Objects::AObject::*)()>(&CappedCone::setMaterial)},
        {"height",      reinterpret_cast<void (Objects::AObject::*)()>(&CappedCone::setHeight)}
};

bool CappedCone::intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const
{
    Vector3 rayToOrigin = ray.origin - _center;

    double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z - ray.direction.y * ray.direction.y;
    double b = 2 * (rayToOrigin.x * ray.direction.x + rayToOrigin.z * ray.direction.z - rayToOrigin.y * ray.direction.y);
    double c = rayToOrigin.x * rayToOrigin.x + rayToOrigin.z * rayToOrigin.z - rayToOrigin.y * rayToOrigin.y;

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        double rootP = (-b - sqrt(discriminant)) / (2 * a);
        double rootN = (-b + sqrt(discriminant)) / (2 * a);
        double distance = std::min(rootP, rootN);

        if (distance >= 0 && distance < tMax && distance > tMin) {
            Vector3 point = ray.at(distance);
            double y = point.y - _center.y;

            if (y < 0) {
                record.intersect = true;
                record.t = distance;
                record.point = point;
                record.normal = (point - _center).normalize();
                record.material = _material;
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

void CappedCone::setCenter(Vector3 center)
{
    _center = center;
}

void CappedCone::setRadius(double radius)
{
    _radius = radius;
}

void CappedCone::setMaterial(Material material)
{
    _material = material;
}

void CappedCone::setHeight(double height)
{
    _height = height;
}
