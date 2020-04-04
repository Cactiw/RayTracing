//
// Created by cactiw on 02.04.2020.
//

#include <fstream>
#include <iterator>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Figure.h"
#include "Square.h"

Figure::Figure(std::vector<Triangle> triangles, Vec3f center, float size, Material material): Object(center, material),
    triangles(triangles){}

std::vector<std::string> split_string(const std::string &str) {
    std::istringstream iss(str);
    return std::vector<std::string> (std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>());
}

// Удаляет в строке всё, после символа '/'
std::vector<std::string> remove_useless_vars(std::vector<std::string> strings) {
    std::vector<std::string> newVector;
    for (auto &str: strings) {
        std::replace(str.begin(), str.end(), '/', ' ');
        newVector.push_back(split_string(str).at(0));
    }
    return newVector;
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
            if (line[1] != ' ') {
                // Нам интересны только вершины полигонов
                continue;
            }
            auto coordinates = split_string(line.substr(2));
            points.emplace_back(center +
            Vec3f(atof(coordinates[0].c_str()),
                    atof(coordinates[1].c_str()),
                    atof(coordinates[2].c_str())) * size);
        } else if (line[0] == 'f') {
            // Добавить полигон (треугольник, или прямоугольник)
            auto point_nums = remove_useless_vars(split_string(line.substr(2)));
            if (point_nums.size() == 3) {
                if (line[1] != ' ') {
                    // Нам интересны только координаты вершин полигонов
                    continue;
                }
                // Добавляем треугольник
                triangles.emplace_back(Triangle(points[atoi(point_nums[0].c_str()) - 1],
                                                points[atoi(point_nums[1].c_str()) - 1],
                                                points[atoi(point_nums[2].c_str()) - 1]));
            } else if (point_nums.size() == 4) {
                // Добавляем прямоугольник
                auto v = Square(points[atoi(point_nums[0].c_str()) - 1],
                        points[atoi(point_nums[1].c_str()) - 1],
                        points[atoi(point_nums[2].c_str()) - 1],
                        points[atoi(point_nums[3].c_str()) - 1]).toVector();
                for (auto t: v) {
                    triangles.push_back(t);
                }
            }
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
