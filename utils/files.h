//
// Created by cactiw on 05.04.2020.
//

#pragma once

#ifndef RT_FILES_H
#define RT_FILES_H

#include <string>

#include "../classes/Color.h"

void save_picture(std::vector<Color> & picture, const std::string &path);
unsigned char * load_picture(const char * &path, int * width, int * height, int * channels);
void close_picture(unsigned char * picture);

#endif //RT_FILES_H
