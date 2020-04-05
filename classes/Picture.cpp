//
// Created by cactiw on 05.04.2020.
//

#include "Picture.h"

#include <utility>

#include "../utils/files.h"

Picture::Picture() {
}

Picture::Picture(const char * path) {
    auto picture = load_picture(path, &width, &height, &channels);
    if (picture == nullptr) {
        return;
    }
    totalPixels = width * height;
    halfPixels = totalPixels / 2;
    colors.reserve(totalPixels);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            int pos = (j * width + i) * 3;
            colors.emplace_back(picture[pos], picture[pos + 1], picture[pos + 2]);
        }
    }
//    for (int j = height-1; j >= 0 ; j--) {
//        for (int i = 0; i < width; i++) {
//            colors[j * (i + 1)] = Color(picture[j * (i + 1) * 3 + 0],
//                    picture[j * (i + 1) * 3 + 1], picture[j * (i + 1) * 3 + 2]);
//        }
//    }
    this->containsPicture = true;
    close_picture(picture);
}

Picture::Picture(std::vector<Color> colors, int width, int height, int channels) : colors(std::move(colors)), width(width),
        height(height), channels(channels){
    totalPixels = width * height;
    halfPixels = totalPixels / 2;
}

std::vector<Color>& Picture::getColors() {
    return colors;
}

int Picture::getWidth() const {
    return this->width;
}

int Picture::getHeight() const {
    return this->height;
}

int Picture::getChannels() const {
    return this->channels;
}

bool Picture::isOpen() const {
    return this->containsPicture;
}

int Picture::getTotalPixels() const {
    return this->totalPixels;
}

int Picture::getHalfPixels() const {
    return this->halfPixels;
}
