#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "stb_image_write.h"

#include "Sphere.h"
#include "vector.cpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION


enum {
    PICTURE_WIDTH = 1024,
    PICTURE_HEIGHT = 768
};


std::vector<Vec3f> generate_picture() {
    std::vector<Vec3f> picture((PICTURE_WIDTH * PICTURE_HEIGHT));
    for (size_t i = 0; i < PICTURE_WIDTH * PICTURE_HEIGHT; ++i) {
        for (size_t j = 0; j < 3; j++) {
            picture[i][j] = int(std::rand() * 255);
        }
    }
    return picture;
}


void save_picture(std::vector<Vec3f> & picture) {
    std::ofstream ofs;
    ofs.open("./out.ppm");
    ofs << "P6\n" << PICTURE_WIDTH << " " << PICTURE_HEIGHT << "\n255\n";
    for (size_t i = 0; i < PICTURE_WIDTH * PICTURE_HEIGHT; ++i) {
        for (size_t j = 0; j < 3; j++) {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, picture[i][j])));
        }
    }
    ofs.close();
}

int main() {
    auto pic = generate_picture();
    save_picture(pic);
    return 0;
}
