//
// Created by Talleux on 08/05/2023.
//

#include "Disk.hpp"

std::unique_ptr<Objects::AObject> Disk::_factory() {
    return std::make_unique<Disk>();
}

bool Disk::_registered = Objects::Factory::_register("Disk", _factory);

std::map<std::string, void (Objects::AObject::*)()> Disk::_propertiesMethods = {
    {"center", reinterpret_cast<void (Objects::AObject::*)()>(&Disk::setCenter)},
    {"normal", reinterpret_cast<void (Objects::AObject::*)()>(&Disk::setNormal)},
    {"radius", reinterpret_cast<void (Objects::AObject::*)()>(&Disk::setRadius)},
    {"material", reinterpret_cast<void (Objects::AObject::*)()>(&Disk::setMaterial)}
};

bool Disk::intersect(const Ray& ray, double tMin, double tMax, Objects::IntersectionRecord& record) const
{
    Vector3 oc = _center - ray.origin;

    double proj = oc.dot(_normal);
    double distance = proj / ray.direction.dot(_normal);
    if (distance < tMin || distance > tMax)
        return false;

    Vector3 point = ray.at(distance);

    if ((point - _center).length() > _radius * _radius)
        return false;

    record.intersect = true;
    record.t = distance;
    record.point = point;
    record.normal = _normal;
    record.material = _material;

    return true;
}

void Disk::setCenter(Vector3 center) {
    _center = center;
}

void Disk::setNormal(Vector3 normal) {
    _normal = normal.normalize();
}

void Disk::setRadius(double radius) {
    _radius = radius;
}

void Disk::setMaterial(Material material) {
    _material = material;
}


