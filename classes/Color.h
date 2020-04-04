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
    Color operator + (const Color &other) const;
    Color operator += (const Color &other);
    Color operator / (float a) const;
};

// Класс для безопасного суммирования цветов (значения - инты, проверок на переполнение нет до момента приведения
// обратно к Color)
class ColorSum {
    int r, g, b;
public:
    ColorSum(int r, int g, int b): r(r), g(g), b(b) {}

    [[nodiscard]] int getR() const;
    [[nodiscard]] int getG() const;
    [[nodiscard]] int getB() const;

    ColorSum operator * (float a) const;
    ColorSum operator + (const Color &other) const;
    ColorSum operator += (const Color &other);
    ColorSum operator / (float a) const;

    [[nodiscard]] Color toColor() const;
};

const Color UNIT_COLOR = Color(1, 1, 1);


#endif //MACHINEGRAPHICS1TASK_COLOR_H
