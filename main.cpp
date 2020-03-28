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
#include "objects/Light.h"


enum {
    PICTURE_WIDTH = 1920,
    PICTURE_HEIGHT = 1080,
    FOV = 70,
    CHANNELS_NUM = 3,
    BACKGROUND_COLOR_1 = 70,
    BACKGROUND_COLOR_2 = 70,
    BACKGROUND_COLOR_3 = 100
};

const Color BACKGROUND_COLOR = Color(BACKGROUND_COLOR_1, BACKGROUND_COLOR_2, BACKGROUND_COLOR_3);

Color cast_ray(Ray &ray, std::vector<Object*> &objects, std::vector<Light*> &lights) {
    float min_dist = std::numeric_limits<float>::max();
    Color color = BACKGROUND_COLOR;
    float brightness = 0, glareBrightness = 0;
    Vec3f hitPoint, normal;
    bool hit = false;
    Object* hitObject = nullptr;
    for (const auto& object: objects) {
        Vec3f tempHitPoint, tempNormal;
        float dist = object->check_intersect(ray, tempHitPoint, tempNormal);
        if (dist > 0 && dist < min_dist) {
            hitPoint = tempHitPoint;
            normal = tempNormal;
            hitObject = object;
//            std::cout << "Intersect " << ray.getTargetPoint().x << " " << ray.getTargetPoint().y << std::endl;
            min_dist = dist;
            color = object->getColor();
            hit = true;  // Для отслеживания наличия пересечений - иначе свет не считаем
        }
    }

    if (hit) {
//        Vec3f toViewer = hitPoint - ray.getBeginPoint();
        for (auto light: lights) {
            Vec3f toLight = (light->getCenter() - hitPoint).normalize();
            brightness += light->getBrightness() * std::max(0.f, toLight.dotProduct(normal));
            Vec3f reflect = ((2 * (toLight.dotProduct(normal)) * normal) - toLight).normalize();
            glareBrightness += std::max(0.f,
                hitObject->getMaterial().getSpecular() * light->getBrightness() *
                powf(reflect.dotProduct(normal), hitObject->getMaterial().getShininess()) * 50);
        }
    } else {
        brightness = 1;
        glareBrightness = 0;
    }
    return color * brightness + UNIT_COLOR * glareBrightness;
}

std::vector<Color> generate_picture(std::vector<Object*> &objects, std::vector<Light*> &lights) {
    std::vector<Color> picture;
    for (size_t i = 0; i < PICTURE_HEIGHT; ++i) {
        for (size_t j = 0; j < PICTURE_WIDTH; ++j) {
//            auto beginPoint = Vec3f(PICTURE_HEIGHT / 2., PICTURE_WIDTH / 2., 0);
            auto beginPoint = Vec3f(PICTURE_WIDTH / 2., PICTURE_HEIGHT / 2., 0);
            auto endPoint = Vec3f(j, i, PICTURE_WIDTH);
            auto ray = Ray(beginPoint, endPoint);
            picture.push_back(cast_ray(ray, objects, lights));
        }
    }
    return picture;
}

Vec3f randomise_point() {
    return Vec3f(int(std::rand() * 255), int(std::rand() * 255), int(std::rand() * 255));
}


void save_picture(std::vector<Color> & picture) {
    stbi_write_jpg("./out.jpg", PICTURE_WIDTH, PICTURE_HEIGHT, CHANNELS_NUM,
            static_cast<void*>(picture.data()), PICTURE_WIDTH * CHANNELS_NUM);
}

void free_resources(std::vector<Object*> &objects) {
    for (auto object: objects) {
        delete object;
    }
}

void add_objects(std::vector<Object*> &objects, std::vector<Light*> &lights) {
    objects.push_back(new Sphere(Vec3f(PICTURE_WIDTH / 2. + 400, PICTURE_HEIGHT / 2. + 350,
                                       PICTURE_WIDTH), Material(Color(30, 30, 180),
                                               1, 1.2, 40), 200));
    objects.push_back(new Sphere(Vec3f(PICTURE_WIDTH / 2. + 250, PICTURE_HEIGHT / 2. - 250,
                                       PICTURE_WIDTH), Material(Color(150, 0, 0),
                                               1, 1.2, 40), 150));
    objects.push_back(new Sphere(Vec3f(PICTURE_WIDTH / 2. - 400, PICTURE_HEIGHT / 2.,
                                       PICTURE_WIDTH + 300),Material(Color(0, 150, 50),
                                               1, 1.2, 40), 100));

    lights.push_back(new Light(Vec3f(PICTURE_WIDTH / 2., PICTURE_HEIGHT / 2., PICTURE_WIDTH - 1000),0.8));
    lights.push_back(new Light(Vec3f(PICTURE_WIDTH, 0, PICTURE_WIDTH - 1000),0.8));
}

int main() {
    std::vector <Object*> objects;
    std::vector <Light*> lights;

    add_objects(objects, lights);

    auto pic = generate_picture(objects, lights);
    save_picture(pic);
    free_resources(objects);
    return 0;
}
