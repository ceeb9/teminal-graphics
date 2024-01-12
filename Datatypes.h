#pragma once

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

class Transform {
    public:
        Point origin;
        Point position;
        float rotation;
        Transform() {}
        Transform(Point input_origin, Point input_position, float input_rotation) {
            this->origin = input_origin;
            this->position = input_position;
            this->rotation = input_rotation;
        }
};
