/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** State
*/

#ifndef State_HPP
#define State_HPP

#include <map>
#include <string>
#include <thread>

#include "Client.hpp"
#include "Display/Display.hpp"
#include "Parser.hpp"
#include "RendererCluster.hpp"
#include "Scene.hpp"
#include "Server.hpp"

class State;

/**
 * @brief Context class
 */
class Context {
    public:
        Context() = default;
        explicit Context(State *state) : _state(state) {};
        ~Context() = default;

        /**
         * @brief Set the current state
         * @param state The state to set
         */
        void setState(State *state);

        /**
         * @brief Get the current state
         * @return The current state
         */
        State *getState();

    private:
        State *_state;
};

/**
 * @brief State class
 */
class State {
    public:
        virtual ~State() = default;

        /**
         * @brief Initialize the state
         * @param parameters The parameters to initialize the state
         */
        virtual void initialize(std::map<std::string, std::string> parameters) = 0;

        /**
         * @brief Run the state
         */
        virtual void run() = 0;

        /**
         * @brief Set the context
         * @param context The context to set
         */
        void setContext(Context *context);

    protected:
        Context *_context;
};

/**
 * @brief RayTracerStates namespace containing all the states of the program
 */
namespace RayTracerStates {
    class LocalMode;
    class ClientMode;
    class ServerMode;
}

/**
 * @brief LocalMode state
 */
class RayTracerStates::LocalMode : public State {
    public:
        void initialize(std::map<std::string, std::string> parameters) override;
        void run() override;

        /**
         * @brief Local Mode thread entrypoint
         * @param rendererCluster The renderer cluster
         * @param display The display
         */
        static void threadEntrypoint(RendererCluster *rendererCluster, Display *display);

    private:
        RendererCluster *_rendererCluster;
        Scene *_scene;
};

/**
 * @brief ClientMode state
 */
class RayTracerStates::ClientMode : public State {
    public:
        void initialize(std::map<std::string, std::string> parameters) override;
        void run() override;

    private:
        std::string _ipAddress;
        int _port;
};

/**
 * @brief ServerMode state
 */
class RayTracerStates::ServerMode : public State {
    public:
        void initialize(std::map<std::string, std::string> parameters) override;
        void run() override;

    private:
        std::string _filepath;
        int _port;
};


#endif /* !State_HPP */
