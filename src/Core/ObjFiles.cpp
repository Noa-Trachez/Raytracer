/*
** EPITECH PROJECT, 2023
** RAYTRACER_OBJFILES_CPP
** File description:
** ObjFiles.cpp
*/

#include "Parser.hpp"
#include <fstream>
#include <iostream>
#include <regex>


void Parser::AllRegex(const std::string &pathFile)
{
    std::ifstream file(pathFile);
    std::vector<Vector3> vertices;

    if (!file.is_open())
        throw Error("Error in opening file", pathFile, 84);
    std::string line;
    while (getline(file, line)) {
        std::regex regex("v (-?[0-9]+.[0-9]+) (-?[0-9]+.[0-9]+) (-?[0-9]+.[0-9]+)");
        std::smatch match;

        if (std::regex_search(line, match, regex)) {
            Vector3 tmp(std::stof(match[1]), std::stof(match[2]), std::stof(match[3]));
            vertices.push_back(tmp);
            continue;
        }

        std::regex regex2("f ([0-9]+)/?[0-9]*/?[0-9]* ([0-9]+)/?[0-9]*/?[0-9]* ([0-9]+)/?[0-9]*/?[0-9]*(?: ([0-9]+)/?[0-9]*/?[0-9]*)?");
        std::smatch match2;

        if (std::regex_match(line, match2, regex2)) {

            if (match2[4] != "") {
                std::unique_ptr<Objects::AObject> tmp2 = Objects::Factory::create("Triangle");
                tmp2->setProperty("material", Material(Vector3(1, 1, 1), Vector3(1, 1, 1), 0.0f, 0.50f, false));
                tmp2->setProperty("a", vertices[std::stoi(match2[1]) - 1]);
                tmp2->setProperty("b", vertices[std::stoi(match2[4]) - 1]);
                tmp2->setProperty("c", vertices[std::stoi(match2[3]) - 1]);
                _objectList.push_back(std::move(tmp2));
            }

            std::unique_ptr<Objects::AObject> tmp = Objects::Factory::create("Triangle");
            tmp->setProperty("material", Material(Vector3(1, 1, 1), Vector3(1, 1, 1), 0.0f, 0.50f, false));
            tmp->setProperty("a", vertices[std::stoi(match2[1]) - 1]);
            tmp->setProperty("b", vertices[std::stoi(match2[2]) - 1]);
            tmp->setProperty("c", vertices[std::stoi(match2[3]) - 1]);
            _objectList.push_back(std::move(tmp));
            continue;
        }
    }
    file.close();
}

void Parser::ParseObjFiles()
{
    if (_cfg.exists("objs") == false)
        return;
    const libconfig::Setting &scenes = _cfg.lookup("objs");

    std::cout << "Parsing obj files" << std::endl;
    const libconfig::Setting &scene = scenes[0];
    std::string name = scene.getName();
    if (name != "Files")
        throw Error("Error in parsing obj files", "Parser", 0);
    for (int i = 0; i < scene.getLength(); i++) {
        const libconfig::Setting &file = scene[i];
        std::string path;
        file.lookupValue("path", path);
        AllRegex(path);
    }
}
