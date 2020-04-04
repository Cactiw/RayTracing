//
// Created by cactiw on 04.04.2020.
//

#ifndef RT_SURFACE_H
#define RT_SURFACE_H


#include "Object.h"
#include "Triangle.h"

class Surface: public Object {
    Triangle triangle;

public:
    Surface(Vec3f a, Vec3f b, Vec3f c, Material material);

    [[nodiscard]] Triangle getTriangle() const;
    float check_intersect(const Ray &ray, Vec3f &hitPoint, Vec3f &normal, Vec3f &trueNormal) const override;
};


#endif //RT_SURFACE_H
