/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** AObject
*/

#ifndef Object_HPP
#define Object_HPP

#include <map>
#include <memory>
#include <vector>

#include "Common.hpp"

/**
 * @brief Drawable object namespace
 */
namespace Objects {
    /**
      * @brief Intersection record structure used to store intersection data (t, point, normal)
      * t is the distance between the ray origin and the intersection point
      * point is the intersection point
      * normal is the normal vector at the intersection point
      */
    typedef struct IntersectionRecord {
        bool intersect = false;
        double t;
        Vector3 point;
        Vector3 normal;
        Material material;
    } IntersectionRecord;


    /**
     * @brief Interface for every drawable object
     * \Important You MUST implement in your final drawable object:<br/>
     *  - A boolean named _registered equal to Objects::Factory::_register({ObjectName}, {FactoryMethod}) <br/>
     *  - A static method named _factory() that return a unique_ptr of your object
     *
     *  Example:
     *  @code{.cpp}
     *  bool MyObject::_registered = Objects::Factory::_register("MyObject", _factory);
     *  std::unique_ptr<Objects::AObject> MyObject::_factory() {
     *  	return std::make_unique<MyObject>();
     *  }
     *  @endcode
     */
    class AObject {
        public:
            virtual ~AObject() = default;

            /**
             * @brief Check if the ray intersect the object
             * @param ray Ray to check
             * @param tMin Minimum distance
             * @param tMax Maximum distance
             * @param record Intersection record to be filled
             * @return True if the ray intersect the object, false otherwise
             */
            virtual bool intersect(const Ray &ray, double tMin, double tMax, Objects::IntersectionRecord &record) const = 0;

            /**
             * @brief Set a property of the object
             * @tparam T Property type
             * @param property Property name
             * @param value Property value
             */
            template<typename T>
            void setProperty(const std::string &property, const T &value)
            {
                auto iter = _propertiesMethods.find(property);
                if (iter == _propertiesMethods.end()) return;

                void (AObject::*setter)(T) = reinterpret_cast<void (AObject::*)(T)>(iter->second);
                (this->*setter)(value);
            }

        protected:
            /**
             * @brief Constructor
             * @param _propertiesMethods Map of properties methods used to set object properties
             */
            explicit AObject(std::map<std::string, void (AObject::*)()> &_propertiesMethods) : _propertiesMethods(_propertiesMethods) {};

        private:
            /**
             * @brief Map of properties methods used to set object properties
             *
             * @note This map is filled by the constructor of the final object.<br />
             * This map can be declared as static in the final object as follow:
             * @code{.cpp}
             * std::map<std::string, void (Objects::AObject::*)()> MyObject::_propertiesMethods = {
             *     {"myproperty", reinterpret_cast<void (Objects::AObject::*)()>(&MyObject::setMyProperty)}
             * };
             * @endcode
             */
            std::map<std::string, void (AObject::*)()> _propertiesMethods;
    };


    /**
     * @brief Factory method for drawable objects
     */
    using factoryMethod = std::unique_ptr<Objects::AObject>(*)();

    /**
     * @brief Factory for drawable objects
     */
    class Factory {
        public:
            /**
             * @brief Last created object serial number
             * @note Debug purpose
             */
            static size_t _serial;

            /**
             * @brief Map of all registered objects
             */
            static std::map<std::string, factoryMethod> _map;

            /**
             * @brief Create a new object
             * @param key AObject name
             * @return A unique_ptr of the object
             */
            static std::unique_ptr<Objects::AObject> create(const std::string &key);

            /**
             * @brief Register a new object in the factory
             * @param key AObject name
             * @param f Factory method
             * @return True if the object has been registered, false otherwise
             */
            static bool _register(const std::string &key, factoryMethod f);
    };
}


#endif /* !Object_HPP */
