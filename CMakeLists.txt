cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -O3")

project (rt)

include(CheckCXXCompilerFlag)

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()


enable_cxx_compiler_flag_if_supported("-std=c++17")
enable_cxx_compiler_flag_if_supported("-fopenmp")
enable_cxx_compiler_flag_if_supported("-O3")
enable_cxx_compiler_flag_if_supported("-Wall")


# get rid of annoying MSVC warnings.
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

set (CMAKE_CXX_STANDARD 17)

add_executable(rt main.cpp computations/vector.cpp objects/Object.h objects/Object.cpp
        objects/Sphere.h objects/Sphere.cpp classes/Ray.cpp classes/Ray.h classes/Color.cpp classes/Color.h
        objects/Light.cpp objects/Light.h classes/Material.cpp classes/Material.h objects/Triangle.cpp objects/Triangle.h)

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
        objects/Light.cpp objects/Light.h classes/Material.cpp classes/Material.h -o rt -O3 -std=c++17 -Wall
)


target_link_libraries(rt ${ALL_LIBS} )

