//
// Created by cactiw on 05.04.2020.
//

#include <iostream>
#include <vector>

#include "files.h"
#include "constants.cpp"


#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../libs/stb/stb_image.h"
#include "../libs/stb/stb_image_write.h"


void save_picture(std::vector<Color> & picture, const std::string &path) {
    stbi_write_jpg(path.data(), PICTURE_WIDTH, PICTURE_HEIGHT, CHANNELS_NUM,
                   static_cast<void*>(picture.data()), PICTURE_WIDTH * CHANNELS_NUM);
}

unsigned char * load_picture(const char * &path, int * width, int * height, int * channels) {
    unsigned char * image = stbi_load(path, width, height, (int *) channels,
            0);
    if (!image) {
        std::cerr << "Error while opening background image" << std::endl;
        return nullptr;
    }
    return image;
}

void close_picture(unsigned char * picture) {
    stbi_image_free(picture);
}
