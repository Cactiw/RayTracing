//
// Created by cactiw on 04.04.2020.
//

#include <iostream>
#include "Square.h"

Square::Square(Vec3f a, Vec3f b, Vec3f c, Vec3f d): t1(a, b, c), t2(a, c, d) {

}

std::vector<Triangle> Square::toVector() const {
    std::vector<Triangle> v;
    v.push_back(t1);
    v.push_back(t2);
    std::cout << "Vector returned" << std::endl;
    return v;
}
