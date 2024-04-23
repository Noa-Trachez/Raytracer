//
// Created by Talleux on 09/05/2023.
//

#ifndef ELLIPSOID_HPP
#define ELLIPSOID_HPP

#include "Object.hpp"

class Ellipsoid : public Objects::AObject {
public:
    Ellipsoid() : AObject(_propertiesMethods) {}
    virtual ~Ellipsoid() = default;

    bool intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const override;

    void setCenter(Vector3 center);
    void setRadii(Vector3 radii);
    void setMaterial(Material material);

private:
    static std::unique_ptr<Objects::AObject> _factory();
    static bool _registered;

    static std::map<std::string, void (Objects::AObject::*)()> _propertiesMethods;

    Vector3 _center;
    Vector3 _radii;
    Material _material;
};

#endif // ELLIPSOID_HPP

