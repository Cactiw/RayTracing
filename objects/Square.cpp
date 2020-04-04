//
// Created by cactiw on 04.04.2020.
//

#include <iostream>
#include "Square.h"

Square::Square(Vec3f a, Vec3f b, Vec3f c, Vec3f d) : t1(a, b, c), t2(a, d, c) {
    float ba = (b - a).norm(), ca = (c - a).norm(), da = (d - a).norm();
    if (ba > ca) {
        if (ba > da) {
            // ba - диагональ
            t1 = Triangle(a, b, c);
            t2 = Triangle(a, b, d);
        } else {
            // da - диагональ
            t1 = Triangle(a, d, b);
            t2 = Triangle(a, d, c);
        }
    } else {
        if (ca > da) {
            // ca - диагональ
            t1 = Triangle(a, c, b);
            t2 = Triangle(a, c, d);
        } else {
            // da - диагональ
            t1 = Triangle(a, d, b);
            t2 = Triangle(a, d, c);
        }
    }
}

std::vector<Triangle> Square::toVector() const {
    std::vector<Triangle> v;
    v.push_back(t1);
    v.push_back(t2);
    return v;
}
