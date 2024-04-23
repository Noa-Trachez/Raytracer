/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Triangle
*/

#include "Triangle.hpp"

bool Triangle::_registered = Objects::Factory::_register("Triangle", _factory);

std::unique_ptr<Objects::AObject> Triangle::_factory()
{
    return std::make_unique<Triangle>();
}

std::map<std::string, void (Objects::AObject::*)()> Triangle::_propertiesMethods = {
    {"a",           reinterpret_cast<void (Objects::AObject::*)()>(&Triangle::setA)},
    {"b",           reinterpret_cast<void (Objects::AObject::*)()>(&Triangle::setB)},
    {"c",           reinterpret_cast<void (Objects::AObject::*)()>(&Triangle::setC)},
    {"material",    reinterpret_cast<void (Objects::AObject::*)()>(&Triangle::setMaterial)}
};

bool Triangle::intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const
{
    const Vector3 edge1 = _b - _a;
    const Vector3 edge2 = _c - _a;
    const Vector3 pvec = ray.direction.cross(edge2);
    const double det = edge1.dot(pvec);

    if (det < EPSILON && det > -EPSILON) return false;

    const double invDet = 1.0 / det;
    const Vector3 tvec = ray.origin - _a;
    const double u = (tvec * pvec).dot(invDet);

    if (u < 0.0 || u > 1.0) return false;

    const Vector3 qvec = tvec.cross(edge1);
    const double v = (ray.direction * qvec).dot(invDet);

    if (v < 0.0 || u + v > 1.0) return false;

    const double t = (edge2 * qvec).dot(invDet);

    if (t <= EPSILON || t < tMin || t > tMax) return false;

    record.intersect = true;
    record.t = t;
    record.point = ray.at(t);
    record.normal = -((edge2.cross(edge1)).normalize() * static_cast<float>(det < 0 ? -1 : 1)).normalize();
    record.material = _material;
    return true;
}

void Triangle::setA(Vector3 a)
{
    _a = a;
}

void Triangle::setB(Vector3 b)
{
    _b = b;
}

void Triangle::setC(Vector3 c)
{
    _c = c;
}

void Triangle::setMaterial(Material material)
{
    _material = material;
}
