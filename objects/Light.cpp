//
// Created by cactiw on 24.03.2020.
//

#include "Light.h"

Light::Light(Vec3f position, float brightness): Object(Vec3f(position), Color(255, 255, 255)) {
    this->brightness = brightness;
}
