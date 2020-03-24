#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

#include "objects/Object.h"
#include "objects/Sphere.h"
#include "classes/Ray.h"
#include "classes/Color.h"
#include "vector.cpp"



enum {
    PICTURE_WIDTH = 1024,
    PICTURE_HEIGHT = 768,
    BACKGROUND_COLOR_1 = 100,
    BACKGROUND_COLOR_2 = 0,
    BACKGROUND_COLOR_3 = 0
};

const Color BACKGROUND_COLOR = Color(BACKGROUND_COLOR_1, BACKGROUND_COLOR_2, BACKGROUND_COLOR_3);

Color cast_ray(Ray &ray, std::vector<Object*> &objects) {
    float min_dist = std::numeric_limits<float>::max();
    Color color = BACKGROUND_COLOR;
    for (const auto& object: objects) {
        float dist = object->check_intersect(ray);
        if (dist > 0 && dist < min_dist) {
            std::cout << "Intersect" << std::endl;
            min_dist = dist;
            color = object->getColor();
        }
    }
    return color;
}

std::vector<Color> generate_picture(std::vector<Object*> &objects) {
    std::vector<Color> picture;
    for (size_t i = 0; i < PICTURE_WIDTH; ++i) {
        for (size_t j = 0; j < PICTURE_HEIGHT; ++j) {
            auto beginPoint = Vec3f(0, 0, 0), endPoint = Vec3f(i, j, 100);
            auto ray = Ray(beginPoint, endPoint);
            picture.push_back(cast_ray(ray, objects));
        }
    }
    return picture;
}

Vec3f randomise_point() {
    return Vec3f(int(std::rand() * 255), int(std::rand() * 255), int(std::rand() * 255));
}


void save_picture(std::vector<Color> & picture) {
    stbi_write_jpg("./out.jpg", PICTURE_WIDTH, PICTURE_HEIGHT, 3, static_cast<void*>(picture.data()), 100);
}

void free_resources(std::vector<Object*> &objects) {
    for (auto object: objects) {
        delete object;
    }
}

int main() {
    std::vector <Object*> objects;

    objects.push_back(new Sphere(Vec3f(10, 10, 150), Color(255, 255, 255), 10));
    auto pic = generate_picture(objects);
    save_picture(pic);
    free_resources(objects);
    return 0;
}
