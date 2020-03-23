cmake_minimum_required(VERSION 3.15)
project(MachineGraphics1Task)

set(CMAKE_CXX_STANDARD 20)

add_executable(MachineGraphics1Task main.cpp vector.cpp objects/Object.h objects/Object.cpp objects/Sphere.h
        objects/Sphere.cpp classes/Ray.cpp classes/Ray.h)