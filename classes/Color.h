//
// Created by cactiw on 24.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_COLOR_H
#define MACHINEGRAPHICS1TASK_COLOR_H


class Color {
    char r, g, b;
public:
    Color(char r, char g, char b): r(r), g(g), b(b) {}

    [[nodiscard]] char getR() const;
    [[nodiscard]] char getG() const;
    [[nodiscard]] char getB() const;
};


#endif //MACHINEGRAPHICS1TASK_COLOR_H
