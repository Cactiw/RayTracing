//
// Created by cactiw on 27.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_MATERIAL_H
#define MACHINEGRAPHICS1TASK_MATERIAL_H


#include "Color.h"

class Material {

    Color color;
    float reflection;
    float specular;

public:
    Material(Color color, float reflection, float specular): color(color), reflection(reflection), specular(specular) {}
    [[nodiscard]] Color getColor() const;
    [[nodiscard]] float getReflection() const;
    [[nodiscard]] float getSpecular() const;
};

const Material BLANK_MATERIAL = Material(Color(0, 0, 0), 0, 0);

#endif //MACHINEGRAPHICS1TASK_MATERIAL_H
