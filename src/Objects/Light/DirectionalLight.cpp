/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"

bool DirectionalLight::_registered = Objects::Factory::_register("DirectionalLight", _factory);

std::unique_ptr<Objects::AObject> DirectionalLight::_factory()
{
    return std::make_unique<DirectionalLight>();
}

std::map<std::string, void (Objects::AObject::*)()> DirectionalLight::_propertiesMethods = {
    {"direction", reinterpret_cast<void (Objects::AObject::*)()>(&DirectionalLight::setDirection)},
    {"color", reinterpret_cast<void (Objects::AObject::*)()>(&DirectionalLight::setColor)},
    {"intensity", reinterpret_cast<void (Objects::AObject::*)()>(&DirectionalLight::setIntensity)}
};

bool DirectionalLight::intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const
{
    // Ratio between the normal and the light direction (0 if the light is behind the object)
    float facingRatio = static_cast<float>(std::max(0.0, ray.direction ^ _direction));

    if (facingRatio <= 0)
        return false;

    record.t = facingRatio;
    record.normal = _direction;
    record.material = Material(_emittedLight);
    return true;
}

void DirectionalLight::setDirection(Vector3 direction)
{
    _direction = direction;
}

void DirectionalLight::setColor(Vector3 color)
{
    _color = color.toColor();
    _emittedLight = _color * _intensity;
}

void DirectionalLight::setIntensity(double intensity)
{
    _intensity = intensity;
    _emittedLight = _color * _intensity;
}
