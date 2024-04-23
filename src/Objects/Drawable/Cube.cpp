#include "Cube.hpp"


std::unique_ptr<Objects::AObject> Cube::_factory() {
    return std::make_unique<Cube>();
}

bool Cube::_registered = Objects::Factory::_register("Cube", Cube::_factory);

std::map<std::string, void (Objects::AObject::*)()> Cube::_propertiesMethods = {
    {"minPoint", reinterpret_cast<void (Objects::AObject::*)()>(&Cube::setMinPoint)},
    {"maxPoint", reinterpret_cast<void (Objects::AObject::*)()>(&Cube::setMaxPoint)},
    {"material", reinterpret_cast<void (Objects::AObject::*)()>(&Cube::setMaterial)}
};

bool Cube::intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const {
    double tMinX = (_minPoint.x - ray.origin.x) / ray.direction.x;
    double tMaxX = (_maxPoint.x - ray.origin.x) / ray.direction.x;

    double tMinY = (_minPoint.y - ray.origin.y) / ray.direction.y;
    double tMaxY = (_maxPoint.y - ray.origin.y) / ray.direction.y;

    double tMinZ = (_minPoint.z - ray.origin.z) / ray.direction.z;
    double tMaxZ = (_maxPoint.z - ray.origin.z) / ray.direction.z;

    // Compute the intersection distances for the near and far planes
    double tNear = std::max({std::min(tMinX, tMaxX), std::min(tMinY, tMaxY), std::min(tMinZ, tMaxZ)});
    double tFar = std::min({std::max(tMinX, tMaxX), std::max(tMinY, tMaxY), std::max(tMinZ, tMaxZ)});

    // Check if the intersection distances are valid and within the specified interval
    if (tNear > tFar || tFar < tMin || tNear > tMax) {
        return false;
    }

    // Compute the intersection point and normal
    Vector3 point = ray.at(tNear);
    Vector3 normal;

    if (tNear == tMinX) {
        normal = Vector3(-1, 0, 0);
    } else if (tNear == tMaxX) {
        normal = Vector3(1, 0, 0);
    } else if (tNear == tMinY) {
        normal = Vector3(0, -1, 0);
    } else if (tNear == tMaxY) {
        normal = Vector3(0, 1, 0);
    } else if (tNear == tMinZ) {
        normal = Vector3(0, 0, -1);
    } else if (tNear == tMaxZ) {
        normal = Vector3(0, 0, 1);
    }

    // Set the intersection record
    record.intersect = true;
    record.t = tNear;
    record.point = point;
    record.normal = normal;
    record.material = _material;

    return true;
}

void Cube::setMinPoint(Vector3 minPoint) {
    _minPoint = minPoint;
}

void Cube::setMaxPoint(Vector3 maxPoint) {
    _maxPoint = maxPoint;
}

void Cube::setMaterial(Material material) {
    _material = material;
}