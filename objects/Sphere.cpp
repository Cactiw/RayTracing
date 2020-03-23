//
// Created by cactiw on 21.03.2020.
//

#include "Sphere.h"

Vec3f Sphere::getCenter() const {
    return this->center;
}

float Sphere::getRadius() const {
    return this->radius;
}

float dot(const Vec3f &point, const Vec3f &center) {
    float norm = (point - center).norm();
    return norm * norm;
}

float Sphere::check_intersect(const Ray &ray) const {
    Vec3f oc = ray.getBeginPoint() - center;
    float a = dot(ray.getTargetPoint(), ray.getTargetPoint());
    float b = 2.0 * dot(oc, ray.getTargetPoint());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    if(discriminant < 0){
        return -1.0;
    } else {
        float numerator = -b - sqrt(discriminant);
        if (numerator > 0.0) {
            return numerator / (2.0 * a);
        }

        numerator = -b + sqrt(discriminant);
        if (numerator > 0.0) {
            return numerator / (2.0 * a);
        }
        else {
            return -1;
        }

    }
}
