#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <omp.h>
#include <cstring>

#include "utils/constants.cpp"
#include "utils/files.h"

#include "objects/Object.h"
#include "objects/Sphere.h"
#include "objects/Light.h"

#include "classes/Ray.h"
#include "classes/Color.h"

#include "computations/vector.cpp"
#include "computations/physics.cpp"
#include "objects/Figure.h"
#include "objects/Surface.h"
#include "classes/Picture.h"

#include "scenes.cpp"

const Color BACKGROUND_COLOR = Color(BACKGROUND_COLOR_1, BACKGROUND_COLOR_2, BACKGROUND_COLOR_3);

Color get_background_color(const Ray &ray, Picture &backgroundImage) {
    if (!backgroundImage.isOpen()) {
        return BACKGROUND_COLOR;
    }
    unsigned int pos = backgroundImage.getWidth() * (int)ray.getTargetPoint().y + ray.getTargetPoint().x;
    if (pos >= backgroundImage.getColors().size()) {
        return BACKGROUND_COLOR;
    }
    return backgroundImage.getColors().at(pos);
}

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
            min_dist = dist;
            color = object->getColor(hitPoint);
        }
    }
    return hitObject != nullptr ? min_dist: -1;
}

Color cast_ray(Ray &ray, std::vector<Object*> &objects, std::vector<Light*> &lights, Picture &backgroundImage,
        int depth = 0) {
    Color color = get_background_color(ray, backgroundImage);
    Color reflectColor = Color(0, 0, 0), refractColor(0, 0, 0);
    if (depth >= DEPTH_LIMIT) {
        return get_background_color(ray, backgroundImage);
    }
    float brightness = 0, glareBrightness = 0;
    Vec3f hitPoint, normal, trueNormal;
    Object* hitObject = nullptr;
    find_first_intersect(ray, objects, hitObject, hitPoint, normal, trueNormal, color);
    bool hit = hitObject != nullptr;

    if (hit) {
        Vec3f originPoint = hitPoint + normal * 1e-1;
        Vec3f originPointInside = hitPoint - normal * 1e-1;
        if (hitObject->getMaterial().getType() == TRANSPARENT) {
            // Вычисление отражение и рефракции
            Ray newRay = Ray(originPoint, originPoint + reflectVector(ray.getDirection(), normal));
            reflectColor = cast_ray(newRay, objects, lights, backgroundImage, depth + 1);

            if (hitObject->getMaterial().isRefractive()) {
                Ray refractionRay(originPointInside,
                        originPointInside +
                            refract(ray.getDirection(), trueNormal, hitObject->getMaterial().getRefractive()).normalize()
                        );
                refractColor = cast_ray(refractionRay, objects, lights, backgroundImage, depth + 1);
            }

        }

        Object* skipObject = nullptr;
        Vec3f skip1, skip2, skip3;
        Color skipColor = get_background_color(ray, backgroundImage);
        for (auto light: lights) {
            Vec3f toLight = light->getCenter() - hitPoint;
            float lightDistance = toLight.norm();
            toLight = toLight.normalize();
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

float count_antialiasing_coefficient(int antialiasing) {
    return 1.f / antialiasing;
}

// Главный цикл генерации картинки
std::vector<std::vector<Color>> generate_picture(std::vector<Object*> &objects, std::vector<Light*> &lights,
        Picture &backgroundImage, int threads, int antialiasing) {
    std::vector<std::vector<Color>> picture(PICTURE_HEIGHT);
    omp_set_num_threads(threads);
    float offset = count_antialiasing_coefficient(antialiasing);
    auto beginPoint = Vec3f(PICTURE_WIDTH / 2., PICTURE_HEIGHT / 2., 0);
    for (size_t i = 0; i < PICTURE_HEIGHT; ++i) {
        std::vector<Color> row(PICTURE_WIDTH, UNIT_COLOR);
        #pragma omp parallel for default(none) shared(row, beginPoint, i, antialiasing, offset, objects, lights, backgroundImage)
        for (size_t j = 0; j < PICTURE_WIDTH; ++j) {
            ColorSum totalColor(0, 0, 0);
            for (int k = 0; k < antialiasing; ++k) {
                auto endPoint = Vec3f(j + offset * k, i + offset * k, PICTURE_WIDTH);
                auto ray = Ray(beginPoint, endPoint);
                totalColor += cast_ray(ray, objects, lights, backgroundImage);
            }
            row[j] = (totalColor / antialiasing).toColor();
        }
        picture.push_back(row);
    }
    #pragma omp barrier
    return picture;
}

void merge_picture(const std::vector<std::vector<Color>> &picture, std::vector<Color> &newImage) {
    newImage.reserve(PICTURE_WIDTH * PICTURE_HEIGHT);
    for (auto &row: picture) {
        std::move(row.begin(), row.end(), std::back_inserter(newImage));
    }
}

template <typename T>
void free_resources(std::vector<T*> &objects) {
    for (auto object: objects) {
        delete object;
    }
}

int main(int argc, char** argv) {
    std::vector <Object*> objects;
    std::vector <Light*> lights;

    Picture backgroundImage{};
    int scene = 1;

    int threads = THREADS_DEFAULT;
    int antialiasing = ANTIALIASING_DEFAULT;
    std::string path = "./out.jpg";
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (strcmp(argv[i], "-threads") == 0) {
                if (i + 1 < argc) {
                    threads = int(strtol(argv[i + 1], nullptr, 10));
                }
            } else if (strcmp(argv[i], "-antialiasing") == 0) {
                if (i + 1 < argc) {
                    antialiasing = int(strtol(argv[i + 1], nullptr, 10));
                }
            } else if (strcmp(argv[i], "-out") == 0) {
                if (i + 1 < argc) {
                    path = argv[i + 1];
                }
            } else if (strcmp(argv[i], "-scene") == 0) {
                if (i + 1 < argc) {
                    scene = int(strtol(argv[i + 1], nullptr, 10));
                    if (scene == 2) {
                        antialiasing = 2;
                    }
                }
            }
        }
    }
    create_scene(objects, lights, backgroundImage, scene);
    auto pic = generate_picture(objects, lights, backgroundImage, threads, antialiasing);
    std::vector<Color> newPicture;
    merge_picture(pic, newPicture);
    save_picture(newPicture, path);
    free_resources(objects);
    free_resources(lights);
    return 0;
}
