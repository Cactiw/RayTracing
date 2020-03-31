//
// Created by cactiw on 31.03.2020.
//

#ifndef RAY_TRACING_PHYSICS
#define RAY_TRACING_PHYSICS

#include <iostream>
#include "vector.cpp"


// Отражение вектора от (зеркальной) поверхности
// v - падающий вектор, normal - нормаль к плоскости
Vec3f reflectVector(const Vec3f &v, const Vec3f &normal) {
    return ((2 * (-v.dotProduct(normal)) * normal) + v).normalize();
}


// Функия в чистом виде имплементирует закон Снеллиуса
// v - падающий вектор, normal - нормаль к плоскости
// refractive_index - индекс рефракции
Vec3f refract(const Vec3f &v, const Vec3f &normal, const float &refractive_index) {
    float cosi = -std::max(-1.f, std::min(1.f, v.dotProduct(normal)));
    float etai = 1, etat = refractive_index;
    Vec3f n = normal;
    if (cosi < 0) {
        // Луч остался внутри объекта. Инвертируем нормаль
        cosi = -cosi;
        std::swap(etai, etat);
        n = -normal;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? Vec3f(0, 0, 0) : v * eta + n * (eta * cosi - sqrtf(k));
}

#endif
