/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"

void Renderer::setScene(Scene *scene)
{
    _scene = scene;
}

void Renderer::renderScene()
{
    for (int y = _scene->imageHeight; y >= 0; y--) {
        for (int x = 0; x < _scene->imageWidth; x++) {
            renderPixel(x, y);

            _frame.setPixel(x, y, sf::Color(static_cast<uint8_t>(255.999 * _currentPixelColor.x),
                static_cast<uint8_t>(255.999 * _currentPixelColor.y),
                static_cast<uint8_t>(255.999 * _currentPixelColor.z)));
        }
    }
}

void Renderer::renderSceneSlice(int xStart, int xEnd, const std::shared_ptr<std::vector<uint8_t>> &pixels)
{
    if (!_scene->progressiveRendering) {
        std::cout << "Fast rendering" << std::endl;
        _scene->rayPerPixel = 1;
    }

    for (int y = _scene->imageHeight; y >= 0; y--) {
        for (int x = xStart; x <= xEnd; x++) {
            renderPixel(x, y);

            (*pixels)[(y * _scene->imageWidth + x) * 3] = static_cast<uint8_t>(_currentPixelColor.x * 255.999);
            (*pixels)[(y * _scene->imageWidth + x) * 3 + 1] = static_cast<uint8_t>(_currentPixelColor.y * 255.999);
            (*pixels)[(y * _scene->imageWidth + x) * 3 + 2] = static_cast<uint8_t>(_currentPixelColor.z * 255.999);
        }
    }
}

void Renderer::renderPixel(int x, int y)
{
    // Ratio between the pixel in the image size
    float u = static_cast<float>(x) / static_cast<float>(_scene->imageWidth - 1);
    float v = static_cast<float>(y) / static_cast<float>(_scene->imageHeight - 1);

    // Point in of the near clipping plane in the local coordinate system (relative to the camera)
    Vector3 localPoint = _scene->localBottomLeftCorner + Vector3(static_cast<float>(_scene->viewportWidth) * u, static_cast<float>(_scene->viewportHeight) * v, 0);

    // Point in the world coordinate system
    Vector3 worldPoint = _scene->cameraPosition + _scene->horizontal * localPoint.x + _scene->vertical * localPoint.y - Vector3(0, 0, 1) * localPoint.z;

    // Fix fisheye distortion
    Vector3 rayDirection = (worldPoint - _scene->cameraPosition).normalize();
    Vector3 rotatedRayDirection = Matrix4::applyBarrelDistortion(rayDirection, _scene->cameraPosition, _scene->cameraDirection).normalize();
    Ray ray(_scene->cameraPosition, rotatedRayDirection);

    // Throw n rays per pixel and average the color
    _currentPixelColor = Vector3(0, 0, 0);
    for (int rayIndex = 0; rayIndex < _scene->rayPerPixel; rayIndex++)
        _currentPixelColor += trace(ray, _scene->_objects);
    _currentPixelColor /= static_cast<float>(_scene->rayPerPixel);
}

// ==================== Raytracing ====================

Vector3 Renderer::trace(Ray &ray, std::vector<std::unique_ptr<Objects::AObject>> &objects, size_t depth)
{
    Vector3 rayColor = Vector3(1, 1, 1);
    Vector3 pixelColor = Vector3(0, 0, 0);
    Ray rayCopy = ray;
    bool rayInVoid = true;

    // Stop the ray if it bounces too much
    if (depth > _scene->maxDepth)
        return Vector3(0, 0, 0);

    for (int bounce = 0; bounce < _scene->maxDepth; bounce++) {
        // Ray intersection
        Objects::IntersectionRecord record;
        if (rayIntersect(rayCopy, objects, record)) {
            rayInVoid = false;

            // Return the emission color for the 1st bounce, so it does calculate shadows on light sources
            if (bounce == 0 && record.material.emissionStrength > 0)
                return record.material.emissionColor * record.material.emissionStrength;
        } else break;

        // Apply when the ray hits an object for the first time
        if (_scene->progressiveRendering && bounce == 0) {
            // Light being cast on every object of the scene
            RTAmbientLight(pixelColor, record);

            // Light being cast on object facing any directional light
            RTDirectionalLight(pixelColor, record);

            // Apply reflectivity on objects
            Ray scattered{};
            if (record.material.reflectivity > 0.0f && RTReflection(ray, record, scattered))
                return (pixelColor * record.material.albedo + trace(scattered, objects, depth + 1)).clamp(0.0f, 1.0f);

            // Apply refraction on objects
            Ray refracted{};
            if (record.material.refractionIndex > 0.0f && RTRefraction(ray, record, refracted))
                return (pixelColor * record.material.albedo + trace(refracted, objects, depth + 1)).clamp(0.0f, 1.0f);
        }
        RTRayCasting(pixelColor, rayColor, record);

        // Ray bounce
        rayCopy.origin = record.point;
        rayCopy.direction = (record.normal + Math::randomDirection()).normalize();

        // Accumulate ray color
        rayColor *= record.material.color;

        // Fast rendering
        if (!_scene->progressiveRendering)
            return rayColor;
    }

    if (_scene->environment && rayInVoid)
        RTEnvironmentLight(pixelColor, rayColor, rayCopy);

    return pixelColor;
}

bool Renderer::rayIntersect(Ray &ray, std::vector<std::unique_ptr<Objects::AObject>> &objects, Objects::IntersectionRecord &record)
{
    Objects::IntersectionRecord currRecord;
    record.t = std::numeric_limits<double>::max();

    for (auto &object: objects) {
        if (object->intersect(ray, EPSILON, record.t, currRecord)) {
            // A closer object has been found
            record = currRecord;
        }
    }
    return record.intersect;
}

void Renderer::RTAmbientLight(Vector3 &pixelColor, Objects::IntersectionRecord &record)
{
    pixelColor += record.material.color * _scene->ambientLight;
    pixelColor.clamp(0.0f, 1.0f);
}

void Renderer::RTDirectionalLight(Vector3 &pixelColor, Objects::IntersectionRecord &record)
{
    Ray lightRay(record.point, record.normal);

    for (auto &directionalLight : _scene->_directionalLight) {
        // Check if a directional light hits the object
        Objects::IntersectionRecord lightRecord;
        Objects::IntersectionRecord shadowRecord;
        if (!directionalLight->intersect(lightRay, 0, 0, lightRecord)) continue;

        // Check if there is an obstacle in between the object and the directional light
        // Shadows won't be cast on reflective objects
        Ray shadowRay(record.point, lightRecord.normal);
        if (rayIntersect(shadowRay, _scene->_objects, shadowRecord) && record.material.reflectivity <= 0.0f) continue;
        pixelColor += record.material.color * lightRecord.material.color * static_cast<float>(lightRecord.t) * record.material.albedo;
    }
    pixelColor.clamp(0.0f, 1.0f);
}

void Renderer::RTRayCasting(Vector3 &pixelColor, Vector3 &rayColor, Objects::IntersectionRecord &record)
{
    Vector3 emittedLight = record.material.emissionColor * record.material.emissionStrength;
    pixelColor += rayColor * emittedLight * record.material.albedo;
    pixelColor.clamp(0.0f, 1.0f);
}

void Renderer::RTEnvironmentLight(Vector3 &pixelColor, Vector3 &rayColor, Ray &ray)
{
    float skyGradientInterpolation = static_cast<float>(std::pow(Math::smoothStep(0.0f, 0.4f, ray.direction.y), 0.35));
    Vector3 skyColorGradient = Math::lerp(Vector3(0.95, 0.95, 0.95), Vector3(0, 0.27, 1.0), skyGradientInterpolation);

    float sun = 0.1f;

    float groundToSkyInterpolation = Math::smoothStep(-0.01f, 0.0f, ray.direction.y);
    float sunMask = groundToSkyInterpolation >= 1;
    Vector3 environmentLight = Math::lerp(Vector3(0.20, 0.20, 0.20), skyColorGradient, groundToSkyInterpolation) + sun * sunMask;
    pixelColor += environmentLight * rayColor;
    pixelColor.clamp(0.0f, 1.0f);
}

bool Renderer::RTReflection(Ray &ray, Objects::IntersectionRecord &record, Ray &scattered)
{
    Vector3 reflected = Math::reflect(ray.direction.normalize(), record.normal);

    scattered = Ray(record.point, reflected + Math::randomInUnitSphere() * record.material.reflectivity);

    return ((scattered.direction ^ record.normal) > 0);
}

bool Renderer::RTRefraction(Ray &ray, Objects::IntersectionRecord &record, Ray &refracted)
{
    double refractionRatio = record.normal ^ ray.direction;

    Vector3 UnitDirection = ray.direction.normalize();
    float cosTheta = std::min(static_cast<float>((-UnitDirection).dot(record.normal)), 1.0f);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0;

    Vector3 direction;
    if (cannotRefract) {
//        direction = reflect(UnitDirection, record.normal);
    } else {
        auto cos_theta = fmin((-UnitDirection).dot(record.normal), 1.0);
        Vector3 r_out_perp =  (UnitDirection + record.normal * cos_theta) * refractionRatio;
        Vector3 r_out_parallel = record.normal * -sqrt(fabs(1.0 - r_out_perp.length()));
        direction = r_out_perp + r_out_parallel;
    }
    refracted = Ray(record.point, direction);
    return true;
}
