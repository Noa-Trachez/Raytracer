/*
** EPITECH PROJECT, 2023
** RAYTRACER_SCENE_CPP
** File description:
** Scene.cpp
*/

#include "Scene.hpp"

void Scene::setObjectList(std::vector<std::unique_ptr<Objects::AObject>> &objectList)
{
    for (auto &object: objectList)
        _objects.push_back(std::move(object));
    objectList.clear();
}

void Scene::setDirectionalLight(std::vector<std::unique_ptr<Objects::AObject>> &directionalLight)
{
    for (auto &light: directionalLight)
        _directionalLight.push_back(std::move(light));
    directionalLight.clear();
}

void Scene::update()
{
    aspectRatio = static_cast<double>(imageWidth) / static_cast<double>(imageHeight);

    horizontal = Vector3(static_cast<float>(viewportWidth), 0, 0);
    vertical = Vector3(0, static_cast<float>(-viewportHeight), 0);

    viewportHeight = nearClippingPlane * std::tan(fieldOfView * 0.5f * DEG_TO_RAD) * 2;
    viewportWidth = viewportHeight * aspectRatio;
    localBottomLeftCorner = Vector3(static_cast<float>(-viewportWidth) / 2, static_cast<float>(-viewportHeight) / 2, static_cast<float>(-nearClippingPlane));
}
