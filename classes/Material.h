//
// Created by cactiw on 27.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_MATERIAL_H
#define MACHINEGRAPHICS1TASK_MATERIAL_H


#include "Color.h"


enum MATERIAL_TYPE {
    NON_TRANSPARENT,
    TRANSPARENT
};

class Material {

    MATERIAL_TYPE type;
    Color color;
    float diffuse;
    float specular;
    float shininess;

public:
    Material(MATERIAL_TYPE type, Color color, float diffuse, float specular, float shininess):
        type(type), color(color), diffuse(diffuse), specular(specular), shininess(shininess) {}

    [[nodiscard]] MATERIAL_TYPE getType() const;
    [[nodiscard]] Color getColor() const;
    [[nodiscard]] float getDiffuse() const;
    [[nodiscard]] float getSpecular() const;
    [[nodiscard]] float getShininess() const;
};

const Material BLANK_MATERIAL = Material(NON_TRANSPARENT,
        Color(0, 0, 0), 0, 0, 0);

#endif //MACHINEGRAPHICS1TASK_MATERIAL_H
