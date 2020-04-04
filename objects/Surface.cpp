//
// Created by cactiw on 04.04.2020.
//

#include "Surface.h"

Surface::Surface(Vec3f a, Vec3f b, Vec3f c, Material material): Object(a, material), triangle(a, b, c) {

}

Triangle Surface::getTriangle() const {
    return this->triangle;
}

float Surface::check_intersect(const Ray &ray, Vec3f &hitPoint, Vec3f &normal, Vec3f &trueNormal) const {
    float t;
    Vec3f T = ray.getBeginPoint() - this->getTriangle().getA();
    Vec3f P = ray.getDirection().crossProduct(this->getTriangle().getE2());
    Vec3f Q = T.crossProduct(this->getTriangle().getE1());
    float K = P.dotProduct(this->getTriangle().getE1());
    if (K == 0) {
        return -1;
    }

    t = Q.dotProduct(this->getTriangle().getE2()) / K;

    if (t > 0) {
        // Попали в плоскость
        //
        normal = this->getTriangle().getNormal().dotProduct(ray.getDirection()) < 0 ? this->getTriangle().getNormal() : - this->getTriangle().getNormal();
        trueNormal = normal; // Может это и неверно, обратить внимание
        hitPoint = ray.getBeginPoint() + ray.getDirection() * t;

        return t;
    } else {
        // Не попали в плоскость (она сзади, или параллельно)
        return -1;
    }
}
