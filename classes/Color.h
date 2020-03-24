//
// Created by cactiw on 24.03.2020.
//

#ifndef MACHINEGRAPHICS1TASK_COLOR_H
#define MACHINEGRAPHICS1TASK_COLOR_H


class Color {
    int r, g, b;
public:
    Color(int r, int g, int b): r(r), g(g), b(b) {}

    [[nodiscard]] int getR() const;
    [[nodiscard]] int getG() const;
    [[nodiscard]] int getB() const;
};


#endif //MACHINEGRAPHICS1TASK_COLOR_H
