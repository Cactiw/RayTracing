//
// Created by cactiw on 31.03.2020.
//
#ifndef MACHINEGRAPHICS1TASK_PHYSICS_H
#define MACHINEGRAPHICS1TASK_PHYSICS_H

#include <iostream>
#include "vector.cpp"


// Отражение вектора от (зеркальной) поверхности
// v - падающий вектор, normal - нормаль к плоскости
Vec3f reflectVector(const Vec3f &v, const Vec3f &normal) {
    return ((2 * (-v.dotProduct(normal)) * normal) + v).normalize();
}


// Функия в чистом виде имплементирует закон Снеллиуса
// v - падающий вектор, normal - нормаль к плоскости
// refractiveIndex - индекс рефракции
Vec3f refract(const Vec3f &v, const Vec3f &normal, const float &refractiveIndex, const float &refractiveIndexAir = 1.f) {
    float cosi = - std::max(-1.f, std::min(1.f, v.dotProduct(normal)));
    if (cosi<0) return refract(v, -normal, refractiveIndexAir, refractiveIndex); // if the ray comes from the inside the object, swap the air and the media
    float eta = refractiveIndexAir / refractiveIndex;
    float k = 1 - eta*eta*(1 - cosi*cosi);
    return k<0 ? Vec3f(1,1,1) : v*eta + normal*(eta*cosi - sqrtf(k));
}

#endif
