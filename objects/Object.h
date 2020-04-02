//
// Created by cactiw on 23.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_OBJECT_H
#define MACHINEGRAPHICS1TASK_OBJECT_H

#include "../computations/vector.cpp"
#include "../classes/Ray.h"
#include "../classes/Color.h"
#include "../classes/Material.h"


class Object {
    Vec3f center;
    Material material;

public:
    Object(Vec3f center, Material material): center(center), material(material) {}

    [[nodiscard]] virtual float check_intersect(const Ray &ray, Vec3f &hitPoint, Vec3f &normal, Vec3f &trueNormal) const {return -1;};

    [[nodiscard]] Vec3f getCenter() const;
    [[nodiscard]] Material getMaterial() const;
    [[nodiscard]] Color getColor() const;

    virtual ~Object();
};


#endif //MACHINEGRAPHICS1TASK_OBJECT_H
