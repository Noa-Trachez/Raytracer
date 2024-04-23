cmake_minimum_required(VERSION 3.22)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

include_directories(.)
include_directories(src/)
include_directories(src/Core)
include_directories(src/Core/Renderer)
include_directories(src/Core/Renderer/Cluster)
include_directories(src/Core/Renderer/Thread)
include_directories(src/Common)
include_directories(src/Objects/Common)
include_directories(src/Objects/Drawable)
include_directories(src/Objects)
include_directories(include)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

include_directories(${libconfig_INCLUDE_DIR})

add_executable(raytracer src/main.cpp
        src/main.hpp
        src/Core/Renderer/Renderer.cpp
        src/Core/Renderer/Renderer.hpp
        src/Objects/Factory/Factory.cpp
        src/Core/Parser.cpp
        src/Core/Parser.hpp
        src/Objects/Common/Common.hpp
        src/Objects/Drawable/Plane.cpp
        src/Objects/Drawable/Plane.hpp
        src/Common/Vector3.cpp
        src/Common/Vector3.hpp
        src/Objects/Common/Ray.cpp
        src/Objects/Common/Ray.hpp
        src/Objects/Drawable/Sphere.cpp
        src/Objects/Drawable/Sphere.hpp
        src/Error_Parsing/ErrorHandling.cpp
        src/Error_Parsing/ErrorHandling.hpp
        src/Common/Math.cpp
        src/Common/Math.hpp
        src/Objects/Common/Material.cpp
        src/Objects/Common/Material.hpp
        src/Objects/Light/DirectionalLight.cpp
        src/Objects/Light/DirectionalLight.hpp
        src/Common/Matrix4.cpp
        src/Common/Matrix4.hpp
        src/Core/Core.cpp src/Core/Core.hpp
        src/Core/Renderer/Cluster/Server.cpp
        src/Core/Renderer/Cluster/Server.hpp
        src/Core/Renderer/Cluster/Client.cpp
        src/Core/Renderer/Cluster/Client.hpp
        src/Core/Renderer/Thread/RendererCluster.cpp
        src/Core/Renderer/Thread/RendererCluster.hpp
        src/Core/Renderer/FrameBuffer.cpp
        src/Core/Renderer/FrameBuffer.hpp
        src/Core/Renderer/Display/Display.cpp
        src/Core/Renderer/Display/Display.hpp
        src/Core/Renderer/Scene.cpp
        src/Objects/Drawable/Triangle.hpp
        src/Objects/Drawable/Triangle.cpp
        src/Objects/Drawable/Cone.cpp
        src/Objects/Drawable/Cone.hpp
        src/Core/State.cpp
        src/Core/State.hpp
        src/Objects/Drawable/Disk.hpp
        src/Objects/Drawable/Disk.cpp
        src/Core/ObjFiles.cpp
        src/Core/State.hpp
        src/Objects/Drawable/Disk.hpp
        src/Objects/Drawable/Disk.cpp
        src/Objects/Drawable/CappedCone.cpp
        src/Objects/Drawable/CappedCone.hpp
        src/Objects/Drawable/Cube.hpp
        src/Objects/Drawable/Cube.cpp
        src/Objects/Drawable/Ellipsoid.hpp
        src/Objects/Drawable/Ellipsoid.cpp
        src/Objects/Drawable/Cylinder.cpp
        src/Objects/Drawable/Cylinder.hpp)

if (APPLE)
    target_link_libraries(raytracer sfml-graphics sfml-window sfml-system sfml-audio /opt/homebrew/lib/libconfig++.dylib dl)
else()
    target_link_libraries(raytracer sfml-graphics sfml-window sfml-system sfml-audio config++ dl)
endif()

set_target_properties(raytracer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})