//
// Created by cactiw on 02.04.2020.
//

#ifndef RT_TRIANGLE_H
#define RT_TRIANGLE_H

#include "../computations/vector.cpp"
#include "../classes/Ray.h"

class Triangle {
    Vec3f a;
    Vec3f b;
    Vec3f c;

    Vec3f e1, e2;
    Vec3f normal;

public:
    Triangle(Vec3f a, Vec3f b, Vec3f c);

    [[nodiscard]] Vec3f getA() const;
    [[nodiscard]] Vec3f getB() const;
    [[nodiscard]] Vec3f getC() const;
    [[nodiscard]] Vec3f getE1() const;
    [[nodiscard]] Vec3f getE2() const;
    [[nodiscard]] Vec3f getNormal() const;

    [[nodiscard]] float check_intersect(const Ray &ray, Vec3f &hitPoint, Vec3f &normal, Vec3f &trueNormal) const;
};


#endif //RT_TRIANGLE_H
