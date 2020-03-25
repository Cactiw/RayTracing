//
// Created by cactiw on 24.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_COLOR_H
#define MACHINEGRAPHICS1TASK_COLOR_H


class Color {
    unsigned char r, g, b;
public:
    Color(unsigned char r, unsigned char g, unsigned char b): r(r), g(g), b(b) {}

    [[nodiscard]] unsigned char getR() const;
    [[nodiscard]] unsigned char getG() const;
    [[nodiscard]] unsigned char getB() const;

    Color operator * (float a) const;
};


#endif //MACHINEGRAPHICS1TASK_COLOR_H
