//
// Created by cactiw on 24.03.2020.
//

#include <iostream>

#include "Color.h"

unsigned char Color::getR() const {
    return this->r;
}

unsigned char Color::getG() const {
    return this->g;
}

unsigned char Color::getB() const {
    return this->b;
}

Color Color::operator*(float a) const {
    return Color(std::min(int(this->getR() * a), 255), std::min(int(this->getG() * a), 255),
            std::min(int(this->getB() * a), 255));
}

Color Color::operator+(const Color &other) const {
    return Color(std::min(int(this->getR() + other.getR()), 255), std::min(int(this->getG() + other.getG()), 255),
                 std::min(int(this->getB() + other.getB()), 255));
}
