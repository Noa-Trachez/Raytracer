/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Parser
*/

#ifndef Parser_HPP
#define Parser_HPP

#include <vector>
#include "Object.hpp"
#include <libconfig.h++>
#include "Error_Parsing/ErrorHandling.hpp"
#include "Scene.hpp"

class Parser {
    public:
        Parser() = default;
        Parser(std::string &path) : _path(path) {};
        ~Parser() = default;

        Scene *parseFile(bool readFromBuffer = false);
        void ParseObjFiles();
        void AllRegex(const std::string &pathFile);

        void setBuffer(std::vector<char> &buffer);

        void ParsePrimitives();
        void ParsingPrimitives(const libconfig::Setting &config);
        static void setMaterial(const libconfig::Setting &config, std::unique_ptr<Objects::AObject> &tmp);
        void ParsingLigths(const libconfig::Setting &config);
        void ParseLights();
        void ParseCamera(Scene *scene);
        void ParseScene(Scene *scene);


private:
        libconfig::Config _cfg;
        std::string _path;
        std::vector<std::unique_ptr<Objects::AObject>> _objectList;
        std::vector<std::unique_ptr<Objects::AObject>> _directionalLight;
        Vector3 _ambient;

        std::vector<char> _buffer;
};


#endif /* !Parser_HPP */
