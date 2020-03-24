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
    CHANNELS_NUM = 3,
    BACKGROUND_COLOR_1 = 0,
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
            std::cout << "Intersect " << ray.getTargetPoint().x << " " << ray.getTargetPoint().y << std::endl;
            min_dist = dist;
            color = object->getColor();
        }
    }
    return color;
}

std::vector<char> generate_picture(std::vector<Object*> &objects) {
    std::vector<char> picture;
    for (size_t i = 0; i < PICTURE_WIDTH; ++i) {
        for (size_t j = 0; j < PICTURE_HEIGHT; ++j) {
            auto beginPoint = Vec3f(0, 0, 0), endPoint = Vec3f(i, j, 100);
            auto ray = Ray(beginPoint, endPoint);
            auto color = cast_ray(ray, objects);
            picture.push_back(color.getR());
            picture.push_back(color.getG());
            picture.push_back(color.getB());
        }
    }
    return picture;
}

Vec3f randomise_point() {
    return Vec3f(int(std::rand() * 255), int(std::rand() * 255), int(std::rand() * 255));
}


void save_picture(std::vector<char> & picture) {

    std::ofstream ofs;
    ofs.open("out.ppm");
    ofs << "P3\n" << PICTURE_WIDTH << " " << PICTURE_HEIGHT << "\n255\n";
    int i = 0;
    for (auto c: picture) {
        ofs << (char)c;
        if (i == 2) {
            ofs << "\n";
            i = 0;
        } else {
            ofs << " ";
            i++;
        }
    }
    ofs.close();
}

void free_resources(std::vector<Object*> &objects) {
    for (auto object: objects) {
        delete object;
    }
}

int main() {
    std::vector <Object*> objects;

    objects.push_back(new Sphere(Vec3f(100, 100, 150), Color(255, 255, 255), 50));
    auto pic = generate_picture(objects);
    save_picture(pic);
    free_resources(objects);
    return 0;
}
