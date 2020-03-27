//
// Created by cactiw on 23.03.2020.
//

#include "../classes/Color.h"
#include "Object.h"

Color Object::getColor() const {
    return this->getMaterial().getColor();
}

Vec3f Object::getCenter() const {
    return this->center;
}

Material Object::getMaterial() const {
    return this->material;
}
