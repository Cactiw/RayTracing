//
// Created by cactiw on 02.04.2020.
// Класс Фигуры из треугольников
//

#ifndef RT_FIGURE_H
#define RT_FIGURE_H


#include <vector>
#include <string>
#include "Object.h"
#include "Triangle.h"

class Figure : public Object{
    std::vector<Triangle> triangles;

public:
    Figure(std::vector<Triangle> triangles, Vec3f center, float size, Material material);
    Figure(const std::string &path, Vec3f center, float size, Material material);

    float check_intersect(const Ray &ray, Vec3f &hitPoint, Vec3f &normal, Vec3f &trueNormal) const override;
};


#endif //RT_FIGURE_H
