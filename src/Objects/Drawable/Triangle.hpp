/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Triangle
*/

#ifndef Triangle_HPP
#define Triangle_HPP

#include "Object.hpp"

class Triangle : public Objects::AObject {
    public:
        Triangle() : AObject(_propertiesMethods) {};
        ~Triangle() override = default;

        bool intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const override;

        void setA(Vector3 a);
        void setB(Vector3 b);
        void setC(Vector3 c);
        void setMaterial(Material material);

    private:
        static std::unique_ptr<Objects::AObject> _factory();
        static bool _registered;

        static std::map<std::string, void (Objects::AObject::*)()> _propertiesMethods;

        Vector3 _a = Vector3(0, 0, -1);
        Vector3 _b = Vector3(0, 0, -1);
        Vector3 _c = Vector3(0, 0, -1);
        Material _material = Material(Vector3(0, 0, 0), Vector3(0, 0, 0), 0);
};


#endif /* !Triangle_HPP */
