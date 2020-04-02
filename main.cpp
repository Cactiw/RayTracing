#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <omp.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

#include "objects/Object.h"
#include "objects/Sphere.h"
#include "objects/Light.h"

#include "classes/Ray.h"
#include "classes/Color.h"

#include "computations/vector.cpp"
#include "computations/physics.cpp"



enum {
    PICTURE_WIDTH = 1920,
    PICTURE_HEIGHT = 1080,
    FOV = 70,
    CHANNELS_NUM = 3,
    BACKGROUND_COLOR_1 = 70,
    BACKGROUND_COLOR_2 = 70,
    BACKGROUND_COLOR_3 = 100,
    DEPTH_LIMIT = 5,
    THREADS_DEFAULT = 4
};

const Color BACKGROUND_COLOR = Color(BACKGROUND_COLOR_1, BACKGROUND_COLOR_2, BACKGROUND_COLOR_3);

// Ищет первое пересечение луча с объектами сцены
float find_first_intersect(const Ray &ray, const std::vector<Object*> &objects, Object* &hitObject,
        Vec3f &hitPoint, Vec3f &normal, Vec3f &trueNormal, Color &color) {
    float min_dist = std::numeric_limits<float>::max();
    for (const auto& object: objects) {
        Vec3f tempHitPoint, tempNormal, tempTrueNormal;
        float dist = object->check_intersect(ray, tempHitPoint, tempNormal, tempTrueNormal);
        if (dist > 0 && dist < min_dist) {
            hitPoint = tempHitPoint;
            normal = tempNormal;
            trueNormal = tempTrueNormal;
            hitObject = object;
//            std::cout << "Intersect " << ray.getTargetPoint().x << " " << ray.getTargetPoint().y << std::endl;
            min_dist = dist;
            color = object->getColor();
        }
    }
    return hitObject != nullptr ? min_dist: -1;
}

Color cast_ray(Ray &ray, std::vector<Object*> &objects, std::vector<Light*> &lights, int depth = 0) {
    Color color = BACKGROUND_COLOR, reflectColor = Color(0, 0, 0), refractColor(0, 0, 0);
    if (depth >= DEPTH_LIMIT) {
        return BACKGROUND_COLOR;
    }
    float brightness = 0, glareBrightness = 0;
    Vec3f hitPoint, normal, trueNormal;
    Object* hitObject = nullptr;
    find_first_intersect(ray, objects, hitObject, hitPoint, normal, trueNormal, color);
    bool hit = hitObject != nullptr;

    if (hit) {
        Vec3f originPoint = hitPoint + normal * 1e-2;
        Vec3f originPointInside = hitPoint - normal * 1e-2;
        if (hitObject->getMaterial().getType() == TRANSPARENT) {
            // Вычисление отражение и рефракции
            Ray newRay = Ray(originPoint, originPoint + reflectVector(ray.getDirection(), normal));
            reflectColor = cast_ray(newRay, objects, lights, depth + 1);

            if (hitObject->getMaterial().isRefractive()) {
                Ray refractionRay(originPointInside,
                        originPointInside +
                            refract(ray.getDirection(), trueNormal, hitObject->getMaterial().getRefractive()).normalize()
                        );
                refractColor = cast_ray(refractionRay, objects, lights, depth + 1);
            }

        }

        Object* skipObject = nullptr;
        Vec3f skip1, skip2, skip3;
        Color skipColor = BACKGROUND_COLOR;
//        Vec3f toViewer = hitPoint - ray.getBeginPoint();
        for (auto light: lights) {
            Vec3f toLight = light->getCenter() - hitPoint;
            float lightDistance = toLight.norm();
            toLight = toLight.normalize();
//            Vec3f originPoint = toLight.dotProduct(normal) > 0 ? hitPoint + normal * 1e-2 : hitPoint - normal * 1e-2;
            Vec3f lightPoint = light->getCenter();
            Ray toLightRay(originPoint, lightPoint);
            float intersectDistance = find_first_intersect(toLightRay, objects, skipObject, skip1, skip2,
                    skip3, skipColor);
            if (intersectDistance > 0 && intersectDistance < lightDistance) {
                // Пересечение, ничего не прибавляем, точка в тени
            } else {
                brightness += light->getBrightness() * std::max(0.f, toLight.dotProduct(normal)); // Свет попадает?

                Vec3f reflect = reflectVector(-toLight, normal);
                glareBrightness += std::max(0.f,
                                            hitObject->getMaterial().getSpecular() * light->getBrightness() *
                                            powf(reflect.dotProduct(normal), hitObject->getMaterial().getShininess()) *
                                            50);
            }
        }
    } else {
        return color;
    }
    return color * brightness +
        UNIT_COLOR * glareBrightness +
        reflectColor * hitObject->getMaterial().getReflectivity() +
        refractColor * 1;
}

// Главный цикл генерации картинки
std::vector<Color> generate_picture(std::vector<Object*> &objects, std::vector<Light*> &lights, int threads) {
    std::vector<Color> picture;
    picture.resize(PICTURE_WIDTH * PICTURE_HEIGHT * sizeof(Color), UNIT_COLOR);
    omp_set_num_threads(threads);
    #pragma omp parallel for
    for (size_t j = 0; j < PICTURE_WIDTH; ++j) {
        #pragma omp parallel for
            for (size_t i = 0; i < PICTURE_HEIGHT; ++i) {
//            auto beginPoint = Vec3f(PICTURE_HEIGHT / 2., PICTURE_WIDTH / 2., 0);
            auto beginPoint = Vec3f(PICTURE_WIDTH / 2., PICTURE_HEIGHT / 2., 0);
            auto endPoint = Vec3f(j, i, PICTURE_WIDTH);
            auto ray = Ray(beginPoint, endPoint);
            picture[j * (i + 1)] = cast_ray(ray, objects, lights);
        }
    }
    #pragma omp barrier
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
    objects.push_back(new Sphere(
            Vec3f(PICTURE_WIDTH / 2. - 150, PICTURE_HEIGHT / 2. - 100, PICTURE_WIDTH - 450),
            GLASS, 150));
    objects.push_back(new Sphere(
            Vec3f(PICTURE_WIDTH / 2., PICTURE_HEIGHT / 2. - 250, PICTURE_WIDTH),
            RED_FULL, 150));
    objects.push_back(new Sphere(
            Vec3f(PICTURE_WIDTH/ 2. + 300, 230, PICTURE_WIDTH - 350),
            GREEN_FULL, 50));


//    objects.push_back(new Sphere(
//            Vec3f(PICTURE_WIDTH/ 2. + 300, 230, +100),
//            GREEN_FULL, 10000));

    lights.push_back(new Light(Vec3f(PICTURE_WIDTH / 2., PICTURE_HEIGHT / 2., PICTURE_WIDTH - 1000),0.8));
//    lights.push_back(new Light(Vec3f(PICTURE_WIDTH, 0, PICTURE_WIDTH - 1000),0.8));
    lights.push_back(new Light(Vec3f(0, 0, PICTURE_WIDTH + 1000),0.8));
    lights.push_back(new Light(Vec3f(300, PICTURE_WIDTH / 2., PICTURE_WIDTH - 1300),0.8));
//    lights.push_back(new Light(Vec3f(PICTURE_WIDTH / 2., PICTURE_HEIGHT / 2., 0),2));
}

int main(int argc, char** argv) {
    std::vector <Object*> objects;
    std::vector <Light*> lights;

    add_objects(objects, lights);

    int threads = THREADS_DEFAULT;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            std::cout << argv[i] << std::endl;
            if (strcmp(argv[i], "-threads") == 0) {
                if (i + 1 < argc) {
                    threads = int(strtol(argv[i + 1], nullptr, 10));
                }
            }
        }
    }
    auto pic = generate_picture(objects, lights, threads);
    save_picture(pic);
    free_resources(objects);
    return 0;
}
