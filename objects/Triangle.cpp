//
// Created by cactiw on 02.04.2020.
//

#include <iostream>
#include "Triangle.h"

Triangle::Triangle(Vec3f a, Vec3f b, Vec3f c): a(a), b(b), c(c) {
    this->e1 = b - a;
    this->e2 = c - a;
    this->normal = e1.crossProduct(e2).normalize();
}

Vec3f Triangle::getA() const {
    return this->a;
}

Vec3f Triangle::getB() const {
    return this->b;
}

Vec3f Triangle::getC() const {
    return this->c;
}

Vec3f Triangle::getE1() const {
    return this->e1;
}

Vec3f Triangle::getE2() const {
    return this->e2;
}

Vec3f Triangle::getNormal() const {
    return this->normal;
}


float Triangle::check_intersect(const Ray &ray, Vec3f &hitPoint, Vec3f &normal, Vec3f &trueNormal) const {
    float t, u, v;
    Vec3f T = ray.getBeginPoint() - this->getA();
    Vec3f P = ray.getDirection().crossProduct(this->getE2());
    Vec3f Q = T.crossProduct(this->getE1());
    float K = P.dotProduct(this->getE1());
    if (K == 0) {
        return -1;
    }

    t = Q.dotProduct(this->getE2()) / K;
    u = P.dotProduct(T) / K;
    v = Q.dotProduct(ray.getDirection()) / K;

    if (u >= 0 && v >= 0 && 1 - u - v >= 0) {
        // Попали в треугольник
        //
        normal = this->getNormal().dotProduct(ray.getDirection()) < 0 ? this->getNormal() : - this->getNormal();
        trueNormal = normal; // Может это и неверно, обратить внимание
        hitPoint = ray.getBeginPoint() + ray.getDirection() * t;

        return t;
    } else {
        // Не попали в треугольник
        return -1;
    }
}
