/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Factory
*/

#include "Object.hpp"

std::map<std::string, Objects::factoryMethod> Objects::Factory::_map;
std::size_t Objects::Factory::_serial = 0;

bool Objects::Factory::_register(const std::string &key, factoryMethod f)
{
    auto object = Factory::_map.find(key);

    if (object == Factory::_map.end()) {
        Factory::_map[key] = f;
        return true;
    }
    return false;
}

std::unique_ptr<Objects::AObject> Objects::Factory::create(const std::string &key)
{
    auto object = Factory::_map.find(key);

    if (object != Factory::_map.end()) {
        Factory::_serial++;
        return object->second();
    }
    return nullptr;
}
