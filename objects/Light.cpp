//
// Created by cactiw on 24.03.2020.
//

#include "Light.h"
#include "../classes/Material.h"

Light::Light(Vec3f position, float brightness): Object(Vec3f(position), BLANK_MATERIAL) {
    this->brightness = brightness;
}

float Light::getBrightness() const {
    return this->brightness;
}
