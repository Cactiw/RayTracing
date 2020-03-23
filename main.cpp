#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "stb_image_write.h"

#include "objects/Object.h"
#include "objects/Sphere.h"
#include "classes/Ray.h"
#include "vector.cpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION


enum {
    PICTURE_WIDTH = 1024,
    PICTURE_HEIGHT = 768,
    BACKGROUND_COLOR_1 = 100,
    BACKGROUND_COLOR_2 = 0,
    BACKGROUND_COLOR_3 = 0
};

const Vec3f BACKGROUND_COLOR = Vec3f(BACKGROUND_COLOR_1, BACKGROUND_COLOR_2, BACKGROUND_COLOR_3);

Vec3f cast_ray(Ray &ray, std::vector<Object> &objects) {
    float min_dist = -1;
    Vec3f color = BACKGROUND_COLOR;
    for (auto object: objects) {
        float dist = object.check_intersect(ray);
        if (dist > 0 && dist < min_dist) {
            min_dist = dist;
            color = object.getColor();
        }
    }
    return color;
}

std::vector<Vec3f> generate_picture(std::vector<Object> &objects) {
    std::vector<Vec3f> picture((PICTURE_WIDTH * PICTURE_HEIGHT));
    for (size_t i = 0; i < PICTURE_WIDTH; ++i) {
        for (size_t j = 0; j < PICTURE_HEIGHT; ++j) {
            auto beginPoint = Vec3f(0, 0, 0), endPoint = Vec3f(i, j, 0);
            auto ray = Ray(beginPoint, endPoint);
            picture[j * i + i] = cast_ray(ray, objects);
        }
    }
    return picture;
}

Vec3f randomise_point() {
    return Vec3f(int(std::rand() * 255), int(std::rand() * 255), int(std::rand() * 255));
}


void save_picture(std::vector<Vec3f> & picture) {
    std::ofstream ofs;
    ofs.open("./out.ppm");
    ofs << "P6\n" << PICTURE_WIDTH << " " << PICTURE_HEIGHT << "\n255\n";
    for (size_t i = 0; i < PICTURE_WIDTH * PICTURE_HEIGHT; ++i) {
        for (size_t j = 0; j < 3; j++) {
            ofs << (picture[i][j]);
        }
    }
    ofs.close();
}

int main() {
    std::vector <Object> objects;

    objects.push_back(Sphere(Vec3f(10, 10, 0), Vec3f(255, 255, 255), 10));
    auto pic = generate_picture(objects);
    save_picture(pic);
    return 0;
}
