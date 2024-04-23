//
// Created by Talleux on 08/05/2023.
//

#ifndef CUBE_HPP
#define CUBE_HPP

#include "Object.hpp"

class Cube : public Objects::AObject {
public:

    Cube() : AObject(_propertiesMethods) {}
    ~Cube() override = default;

    bool intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const override;

    void setMinPoint(Vector3 minPoint);
    void setMaxPoint(Vector3 maxPoint);
    void setMaterial(Material material);

private:
    static std::unique_ptr<Objects::AObject> _factory();
    static bool _registered;

    static std::map<std::string, void (Objects::AObject::*)()> _propertiesMethods;

    Vector3 _minPoint;
    Vector3 _maxPoint;
    Material _material;
};

#endif // CUBE_HPP



