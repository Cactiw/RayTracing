cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -O3")

project (rt)

# get rid of annoying MSVC warnings.
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

set (CMAKE_CXX_STANDARD 17)

add_executable(rt main.cpp computations/vector.cpp objects/Object.h objects/Object.cpp
        objects/Sphere.h objects/Sphere.cpp classes/Ray.cpp classes/Ray.h classes/Color.cpp classes/Color.h
        objects/Light.cpp objects/Light.h classes/Material.cpp classes/Material.h)

add_custom_target(clean-all
   COMMAND ${CMAKE_BUILD_TOOL} clean
   COMMAND rm -r CMakeCache.txt cmake_install.cmake CMakeFiles Makefile
)

add_custom_target(run
   COMMAND make
   COMMAND ./rt
)

add_custom_target(omp
   COMMAND g++ -fopenmp main.cpp computations/vector.cpp objects/Object.h objects/Object.cpp
        objects/Sphere.h objects/Sphere.cpp classes/Ray.cpp classes/Ray.h classes/Color.cpp classes/Color.h
        objects/Light.cpp objects/Light.h classes/Material.cpp classes/Material.h -o rt -O3 -std=c++17
)


target_link_libraries(rt ${ALL_LIBS} )

