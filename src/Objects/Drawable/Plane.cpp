/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Plane
*/

#include "Plane.hpp"

bool Plane::_registered = Objects::Factory::_register("Plane", _factory);

std::unique_ptr<Objects::AObject> Plane::_factory()
{
    return std::make_unique<Plane>();
}

std::map<std::string, void (Objects::AObject::*)()> Plane::_propertiesMethods = {
    {"axis",     reinterpret_cast<void (Objects::AObject::*)()>(&Plane::setAxis)},
    {"position", reinterpret_cast<void (Objects::AObject::*)()>(&Plane::setPosition)},
    {"material", reinterpret_cast<void (Objects::AObject::*)()>(&Plane::setMaterial)}
};

bool Plane::intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const
{
    const double denominator = _axis ^ ray.direction;

    // Denominator == 0: the ray is perpendicular to the plane
    // Denominator > 0: the ray is facing the plane
    // Denominator < 0: the ray is facing the opposite direction of the plane
    if (std::abs(denominator) > EPSILON) {
        const double t = -((_axis ^ ray.origin) + _position) / (_axis ^ ray.direction);
        const double distance = std::abs(((_pointOnPlane - ray.origin) ^ _axis) / denominator);

        if (t <= EPSILON || distance < tMin || distance > tMax) return false;

        record.intersect = true;
        record.t = distance;
        record.point = ray.at(t);
        record.normal = _axis;
        record.material = _material;
        return true;
    }
    return false;
}

void Plane::setAxis(Vector3 axis)
{
    _axis = axis.normalize();
    _pointOnPlane = _axis * static_cast<float>(_position);
}

void Plane::setPosition(double position)
{
    _position = position;
    _pointOnPlane = _axis * static_cast<float>(_position);
}

void Plane::setMaterial(Material material)
{
    _material = material;
}
