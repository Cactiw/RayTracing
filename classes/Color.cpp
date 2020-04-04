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

Color Color::operator+=(const Color &other) {
    this->r += other.getR();
    this->g += other.getG();
    this->b += other.getB();
    return *this;
}

Color Color::operator/(const float a) const {
    return Color(this->getR() / a, this->getG() / a, this->getB() / a);
}




int ColorSum::getR() const {
    return this->r;
}

int ColorSum::getG() const {
    return this->g;
}

int ColorSum::getB() const {
    return this->b;
}

ColorSum ColorSum::operator*(float a) const {
    return ColorSum(std::min(int(this->getR() * a), 255), std::min(int(this->getG() * a), 255),
            std::min(int(this->getB() * a), 255));
}

ColorSum ColorSum::operator+(const Color &other) const {
    return ColorSum(this->getR() + other.getR(), this->getG() + other.getG(), this->getB() + other.getB());
}

ColorSum ColorSum::operator+=(const Color &other) {
    this->r += other.getR();
    this->g += other.getG();
    this->b += other.getB();
    return *this;
}

ColorSum ColorSum::operator/(const float a) const {
    return ColorSum(this->getR() / a, this->getG() / a, this->getB() / a);
}

Color ColorSum::toColor() const {
    return Color(std::min(this->getR(), 255), std::min(this->getG(), 255), std::min(this->getB(), 255));
}
