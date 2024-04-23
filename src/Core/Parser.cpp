/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Parser
*/

#include "Parser.hpp"

void Parser::ParsingPrimitives(const libconfig::Setting &config)
{
    std::string type = config.getName();
    for (int i = 0; i < config.getLength(); i++) {
        const libconfig::Setting &prim = config[i];
        std::unique_ptr<Objects::AObject> tmp = Objects::Factory::create(type);
        if (tmp == nullptr) {
            std::string message = "Error: Unknown primitive type: ";
            message += config.getName();
            throw Error(message, "Parser::ParsingPrimitives", 84);
        }

        for (auto &it: prim) {
            if (it.getType() == 4) {
                std::string val;
                prim.lookupValue(it.getName(), val);
                tmp->setProperty(it.getName(), val);
            }
            if (it.getType() == 1) {
                int val = 0;
                prim.lookupValue(it.getName(), val);
                double val2 = static_cast<float>(val);
                tmp->setProperty(it.getName(), val2);
            }
            if (it.getType() == 3) {
                float val = 0;
                prim.lookupValue(it.getName(), val);
                double val2 = val;
                tmp->setProperty(it.getName(), val2);
            }
            if (it.getType() == 6) {
                setMaterial(it, tmp);
            }
        }
        if (type == "DirectionalLight") {
            _directionalLight.push_back(std::move(tmp));
            continue;
        }
        _objectList.push_back(std::move(tmp));
    }
}

void Parser::setMaterial(const libconfig::Setting &it, std::unique_ptr<Objects::AObject> &tmp)
{
    std::string name = it.getName();
    if (name == "material") {
        Vector3 first;
        Vector3 second;
        float third = 0;
        for (int i = 0; i < 3; i++) {
            int a = 0;
            it.lookupValue(it[i].getName(), a);
            first[i] = static_cast<float>(a);
        }
        for (int i = 3; i < 6; i++) {
            int a = 0;
            it.lookupValue(it[i].getName(), a);
            second[i % 3] = static_cast<float>(a);
        }
        it.lookupValue(it[6].getName(), third);
        float reflectivity = 0.0f;
        it.lookupValue(it[7].getName(), reflectivity);
        float refraction = 0.0f;
        it.lookupValue(it[8].getName(), refraction);

        tmp->setProperty("material", Material(first, second, third, 0.50f, reflectivity, refraction));
    } else {
        Vector3 vec;
        for (int i = 0; i < 3; i++) {
            int a = 0;
            if (it[i].getType() == 1) {
                it.lookupValue(it[i].getName(), a);
                vec[i] = static_cast<float>(a);
            } else
                it.lookupValue(it[i].getName(), vec[i]);
        }
        tmp->setProperty(it.getName(), vec);
    }
}

void Parser::ParsePrimitives()
{
    if (!_cfg.exists("primitives"))
        return;
    const libconfig::Setting &primitives = _cfg.lookup("primitives");
    if (primitives.getLength() > 0) {
        for (int i = 0; i < primitives.getLength(); i++) {
            const libconfig::Setting &primitive = primitives[i];
            ParsingPrimitives(primitive);
        }
    }
}

void Parser::ParsingLigths(const libconfig::Setting &config)
{
    std::string type = config.getName();

    if (type == "ambientLight") {
        Vector3 vec;
        for (int i = 0; i < 3; i++) {
            int a = 0;
            if (config[i].getType() == 1) {
                config.lookupValue(config[i].getName(), a);
                vec[i] = static_cast<float>(a);
            } else
                config.lookupValue(config[i].getName(), vec[i]);
        }
        _ambient = vec;
        return;
    }

    ParsingPrimitives(config);
}

void Parser::ParseLights()
{
    if (!_cfg.exists("lights"))
        return;
    const libconfig::Setting &primitives = _cfg.lookup("lights");

    for (int i = 0; i < primitives.getLength(); i++) {
        const libconfig::Setting &primitive = primitives[i];
        ParsingLigths(primitive);
    }
}

void Parser::ParseCamera(Scene *scene)
{
    const libconfig::Setting &camera = _cfg.lookup("camera");
    const libconfig::Setting &resolution = camera["resolution"];
    const libconfig::Setting &position = camera["position"];
    const libconfig::Setting &rotation = camera["rotation"];

    camera.lookupValue("fieldOfView", scene->fieldOfView);

    resolution.lookupValue("width", scene->imageWidth);
    resolution.lookupValue("height", scene->imageHeight);

    position.lookupValue("x", scene->cameraPosition[0]);
    position.lookupValue("y", scene->cameraPosition[1]);
    position.lookupValue("z", scene->cameraPosition[2]);

    rotation.lookupValue("x", scene->cameraDirection[0]);
    rotation.lookupValue("y", scene->cameraDirection[1]);
    rotation.lookupValue("z", scene->cameraDirection[2]);
}

void Parser::ParseScene(Scene *scene)
{
    const libconfig::Setting &scenes = _cfg.lookup("scene");

    scenes.lookupValue("rayPerPixel", scene->rayPerPixel);
    scenes.lookupValue("progressiveRendering", scene->progressiveRendering);
    scenes.lookupValue("maxDepth", scene->maxDepth);
    scenes.lookupValue("environment", scene->environment);
}

Scene *Parser::parseFile(bool readFromBuffer)
{
    auto *scene = new Scene();

    try {
        _objectList.clear();
        _directionalLight.clear();

        if (readFromBuffer)
            _cfg.readString(_buffer.data());
        else
            _cfg.readFile(_path.c_str());

        ParseCamera(scene);
        ParseScene(scene);
        ParsePrimitives();
        ParseLights();
        ParseObjFiles();

        scene->ambientLight = _ambient;
        scene->setObjectList(_objectList);
        scene->setDirectionalLight(_directionalLight);
        scene->update();
    }
    catch (std::exception &e) {
        delete scene;
        std::cerr << e.what() << std::endl;
        throw Error("Invalid scene file", "main.cpp", 84);
    }
    return scene;
}

void Parser::setBuffer(std::vector<char> &buffer)
{
    _buffer = buffer;
}
