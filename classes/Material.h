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
    float reflectivity;
    float specular;
    float refractive;
    float shininess;

public:
    Material(MATERIAL_TYPE type, Color color, float reflectivity, float specular, float refractive, float shininess):
            type(type), color(color), reflectivity(reflectivity), specular(specular), refractive(refractive), shininess(shininess) {}

    [[nodiscard]] MATERIAL_TYPE getType() const;
    [[nodiscard]] Color getColor() const;
    [[nodiscard]] float getReflectivity() const;
    [[nodiscard]] float getSpecular() const;
    [[nodiscard]] float getRefractive() const;
    [[nodiscard]] float getShininess() const;

    [[nodiscard]] bool isRefractive() const;
};

const Material BLANK_MATERIAL = Material(NON_TRANSPARENT,
        Color(0, 0, 0), 0, 0, 0, 0);

const Material BLUE_FULL = Material(NON_TRANSPARENT, Color(30, 30, 180),
                                    0, 1.2, 0, 40);
const Material RED_FULL = Material(NON_TRANSPARENT, Color(150, 0, 0),
                                   0, 1.2, 0, 40);
const Material GREEN_FULL = Material(NON_TRANSPARENT, Color(0, 150, 50),
                                     0, 1.2, 0, 40);
const Material YELLOW_FULL = Material(NON_TRANSPARENT, Color(242, 249, 59),
                                     0, 1.2, 0, 40);
const Material ORANGE_FULL = Material(NON_TRANSPARENT, Color(255, 206, 90),
                                     0, 1.2, 0, 40);
const Material WhITE_FULL = Material(NON_TRANSPARENT, Color(255, 255, 255),
                                     0, 1.2, 0, 40);


const Material MIRROR = Material(TRANSPARENT, Color(100, 100, 100),
        1, 1.2, 0, 10);
const Material GLASS = Material(TRANSPARENT, Color(100, 100, 100),
        0, 1.2, 1.4, 10);
const Material CLEAN_GLASS = Material(TRANSPARENT, Color(30, 30, 30),
        0, 1.2, 1, 10);

#endif //MACHINEGRAPHICS1TASK_MATERIAL_H
