/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** DirectionalLight
*/

#ifndef DirectionalLight_HPP
#define DirectionalLight_HPP

#include "Object.hpp"

class DirectionalLight : public Objects::AObject {
    public:
        DirectionalLight() : AObject(_propertiesMethods) {};
        ~DirectionalLight() override = default;

        bool intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const override;

        void setDirection(Vector3 direction);
        void setColor(Vector3 color);
        void setIntensity(double intensity);

    private:
        static std::unique_ptr<Objects::AObject> _factory();
        static bool _registered;

        static std::map<std::string, void (Objects::AObject::*)()> _propertiesMethods;

        Vector3 _direction = Vector3(0, 0, 0);
        Vector3 _color = Vector3(0, 0, 0);
        float _intensity = 0.0f;

        Vector3 _emittedLight = _color * _intensity;
};


#endif /* !DirectionalLight_HPP */
