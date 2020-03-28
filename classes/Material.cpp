//
// Created by cactiw on 27.03.2020.
//

#include "Material.h"

Color Material::getColor() const {
    return this->color;
}

float Material::getDiffuse() const {
    return this->diffuse;
}

float Material::getSpecular() const {
    return this->specular;
}

float Material::getShininess() const {
    return this->shininess;
}
