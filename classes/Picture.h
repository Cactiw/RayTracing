//
// Created by cactiw on 05.04.2020.
//

#ifndef RT_PICTURE_H
#define RT_PICTURE_H


#include <vector>
#include "Color.h"

class Picture {
    std::vector<Color> colors;
    bool containsPicture = false;
    int width, height, channels;
    int totalPixels, halfPixels;

public:
    Picture();
    Picture(const char * path);
    Picture(std::vector<Color> colors, int width, int height, int channels);

    [[nodiscard]] bool isOpen() const;
    [[nodiscard]] std::vector<Color>& getColors();
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] int getTotalPixels() const;
    [[nodiscard]] int getHalfPixels() const;
    [[nodiscard]] int getChannels() const;
};


#endif //RT_PICTURE_H
