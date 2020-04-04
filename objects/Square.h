//
// Created by cactiw on 04.04.2020.
//

#ifndef RT_SQUARE_H
#define RT_SQUARE_H


#include <vector>
#include "Triangle.h"

class Square {
    Triangle t1, t2;

public:
    Square(Vec3f a, Vec3f b, Vec3f c, Vec3f d);
    [[nodiscard]] std::vector<Triangle> toVector() const;
};


#endif //RT_SQUARE_H
