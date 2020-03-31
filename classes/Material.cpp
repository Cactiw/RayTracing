//
// Created by cactiw on 27.03.2020.
//

#include "Material.h"

Color Material::getColor() const {
    return this->color;
}

float Material::getReflectivity() const {
    return this->reflectivity;
}

float Material::getSpecular() const {
    return this->specular;
}

float Material::getShininess() const {
    return this->shininess;
}

MATERIAL_TYPE Material::getType() const {
    return this->type;
}

float Material::getRefractive() const {
    return this->refractive;
}

bool Material::isRefractive() const {
    return this->getRefractive() != 0;
}
