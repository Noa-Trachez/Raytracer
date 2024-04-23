//
// Created by Talleux on 09/05/2023.
//

#include "Ellipsoid.hpp"

std::unique_ptr<Objects::AObject> Ellipsoid::_factory() {
    return std::make_unique<Ellipsoid>();
}

bool Ellipsoid::_registered = Objects::Factory::_register("Ellipsoid", _factory);

std::map<std::string, void (Objects::AObject::*)()> Ellipsoid::_propertiesMethods = {
    {"center", reinterpret_cast<void (Objects::AObject::*)()>(&Ellipsoid::setCenter)},
    {"radii", reinterpret_cast<void (Objects::AObject::*)()>(&Ellipsoid::setRadii)},
    {"material", reinterpret_cast<void (Objects::AObject::*)()>(&Ellipsoid::setMaterial)}
};

bool Ellipsoid::intersect(const Ray& ray, double tMin, double tMax, Objects::IntersectionRecord& record) const {
    Vector3 oc = ray.origin - _center;

    double a = ray.direction.x * ray.direction.x / (_radii.x * _radii.x) +
        ray.direction.y * ray.direction.y / (_radii.y * _radii.y) +
        ray.direction.z * ray.direction.z / (_radii.z * _radii.z);
    double b = 2 * (ray.direction.x * oc.x / (_radii.x * _radii.x) +
        ray.direction.y * oc.y / (_radii.y * _radii.y) +
        ray.direction.z * oc.z / (_radii.z * _radii.z));
    double c = oc.x * oc.x / (_radii.x * _radii.x) +
        oc.y * oc.y / (_radii.y * _radii.y) +
        oc.z * oc.z / (_radii.z * _radii.z) - 1;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false;
    }

    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);

    if (t1 < tMin || t1 > tMax) {
        if (t2 < tMin || t2 > tMax) {
            return false;
        }
        std::swap(t1, t2);
    }

    Vector3 point = ray.at(t1);

    Vector3 normal = Vector3(2 * point.x / (_radii.x * _radii.x),
        2 * point.y / (_radii.y * _radii.y),
        2 * point.z / (_radii.z * _radii.z)).normalize();

    record.intersect = true;
    record.t = t1;
    record.point = point;
    record.normal = normal;
    record.material = _material;

    return true;
}

void Ellipsoid::setCenter(Vector3 center) {
    _center = center;
}

void Ellipsoid::setRadii(Vector3 radii) {
    _radii = radii;
}

void Ellipsoid::setMaterial(Material material) {
    _material = material;
}
