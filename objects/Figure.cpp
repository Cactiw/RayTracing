//
// Created by cactiw on 02.04.2020.
//

#include <fstream>
#include <iterator>
#include <sstream>
#include <iostream>
#include "Figure.h"

Figure::Figure(std::vector<Triangle> triangles, Vec3f center, float size, Material material): Object(center, material),
    triangles(triangles){}

std::vector<std::string> split_string(const std::string &str) {
    std::istringstream iss(str);
    return std::vector<std::string> (std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>());
}


Figure::Figure(const std::string &path, Vec3f center, float size, Material material): Object(center, material) {
    std::ifstream f;
    f.open(path);
    std::string line;
    std::vector<Vec3f> points;
    std::vector<Triangle> triangles;
    while (std::getline(f, line)) {
        if (line[0] == 'v') {
            // Добавить точку
            auto coordinates = split_string(line.substr(2));
            points.emplace_back(center +
            Vec3f(atof(coordinates[0].c_str()),
                    atof(coordinates[1].c_str()),
                    atof(coordinates[2].c_str())) * size);
//            std::cout << atof(coordinates[0].c_str()) << " " << atof(coordinates[1].c_str()) << " " <<
//                    atof(coordinates[2].c_str()) << std::endl;
        } else if (line[0] == 'f') {
            // Добавить треугольник
            auto point_nums = split_string(line.substr(2));
            triangles.emplace_back(Triangle(points[atoi(point_nums[0].c_str()) - 1],
                    points[atoi(point_nums[1].c_str()) - 1], points[atoi(point_nums[2].c_str()) - 1]));
        }
    }
    f.close();
    this->triangles = triangles;
}


float Figure::check_intersect(const Ray &ray, Vec3f &hitPoint, Vec3f &normal, Vec3f &trueNormal) const {
    float min_dist = std::numeric_limits<float>::max();
    bool hit = false;
    for (auto const &triangle: this->triangles) {
        Vec3f tempHitPoint, tempNormal, tempTrueNormal;
        float dist = triangle.check_intersect(ray, tempHitPoint, tempNormal, tempTrueNormal);
        if (dist > 0 && dist < min_dist) {
            min_dist = dist;

            hitPoint = tempHitPoint;
            normal = tempNormal;
            trueNormal = tempTrueNormal;
            hit = true;
        }
    }
    return hit ? min_dist : -1;
}
