//
// Created by cactiw on 21.03.2020.
//

#include <iostream>
#include "Sphere.h"

float Sphere::getRadius() const {
    return this->radius;
}

float dot(const Vec3f &point, const Vec3f &center) {
    float norm = (point - center).norm();
    return norm * norm;
}

float Sphere::check_intersect(const Ray &ray) const {
    //std::cout << "check_intersect" << std::endl;
    float t0, t1;
    Vec3f L = getCenter() - ray.getBeginPoint();
    float tca = L.dotProduct(ray.getTargetPoint());
    // if (tca < 0) return false;
    float d2 = L.dotProduct(L) - tca * tca;
    if (d2 > radius2) return -1;
    float thc = sqrt(radius2 - d2);
    t0 = tca - thc;
    t1 = tca + thc;
    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
        t0 = t1; // if t0 is negative, let's use t1 instead
        if (t0 < 0) return -1; // both t0 and t1 are negative
    }

    float t = t0;

    return t;
}
