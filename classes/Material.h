//
// Created by cactiw on 27.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_MATERIAL_H
#define MACHINEGRAPHICS1TASK_MATERIAL_H


#include "Color.h"

class Material {

    Color color;
    float diffuse;
    float specular;
    float shininess;

public:
    Material(Color color, float diffuse, float specular, float shininess):
        color(color), diffuse(diffuse), specular(specular), shininess(shininess) {}
    [[nodiscard]] Color getColor() const;
    [[nodiscard]] float getDiffuse() const;
    [[nodiscard]] float getSpecular() const;
    [[nodiscard]] float getShininess() const;
};

const Material BLANK_MATERIAL = Material(Color(0, 0, 0), 0, 0, 0);

#endif //MACHINEGRAPHICS1TASK_MATERIAL_H
