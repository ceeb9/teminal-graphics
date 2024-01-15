#pragma once
#include <cmath>
#include <vector>

class Color {
    public:
        int red;
        int green;
        int blue;
        Color() {}
        Color(int input_red, int input_green, int input_blue) {
            this->red = input_red;
            this->green = input_green;
            this->blue = input_blue;
        }

        bool operator==(const Color& other) {
            if (this->red == other.red && this->green == other.green && this->blue == other.blue) {
                return true;
            }
            else {
                return false;
            }
        }

        bool operator!=(const Color& other) {
            return !(*this == other);
        }
};

class Point {
    public:
        float x;
        float y;
        Point() {}
        Point(float input_x, float input_y) {
            this->x = input_x;
            this->y = input_y;
        }
};

class DiscretePoint {
    public:
        int x;
        int y;
        DiscretePoint() {}
        DiscretePoint(int input_x, int input_y) {
            this->x = input_x;
            this->y = input_y;
        }
};

class Pixel {
    public:
        DiscretePoint pos;
        Color color;
        Pixel() {}
        Pixel(DiscretePoint input_point, Color input_color) {
            this->pos = input_point;
            this->color = input_color;
        }
        Pixel(int x, int y, Color input_color) {
            this->pos = DiscretePoint(x, y);
            this->color = input_color;
        }
};

