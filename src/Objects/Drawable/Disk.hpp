//
// Created by Talleux on 08/05/2023.
//

#ifndef DISK_HPP
#define DISK_HPP

#include "Object.hpp"

class Disk : public Objects::AObject {
public:
    Disk() : AObject(_propertiesMethods) {}
    ~Disk() override = default;

    bool intersect(const Ray& ray, double tMin, double tMax, Objects::IntersectionRecord& record) const override;

    void setCenter(Vector3 center);
    void setNormal(Vector3 normal);
    void setRadius(double radius);
    void setMaterial(Material material);

private:
    static std::unique_ptr<Objects::AObject> _factory();
    static bool _registered;

    static std::map<std::string, void (Objects::AObject::*)()> _propertiesMethods;

    Vector3 _center = Vector3(0, 0, 0);
    Vector3 _normal = Vector3(0, 0, 0);
    double _radius = 0.0;
    Material _material = Material(Vector3(0, 0, 0), Vector3(0, 0, 0), 0.0);
};

#endif // DISK_HPP


