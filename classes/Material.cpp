//
// Created by cactiw on 27.03.2020.
//

#include "Material.h"

Color Material::getColor() const {
    return this->color;
}

float Material::getReflection() const {
    return this->reflection;
}

float Material::getSpecular() const {
    return this->specular;
}
