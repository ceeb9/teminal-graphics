#pragma once
#include <list>

enum class InputStateChange {
    Q_UP,
    Q_DOWN,
    W_UP,
    W_DOWN
};

class ProgramStateInfo {
    public:
        int framecount;
        std::list<InputStateChange> input_queue;
        int canvas_size_x;
        int canvas_size_y;
};

class DiscretePoint {
    public:
        int x;
        int y;
        DiscretePoint() : x(0), y(0){};
        DiscretePoint(int new_x, int new_y) : x(new_x), y(new_y){};
};

class Color {
    public:
        int red;
        int green;
        int blue;
        Color(){}
        Color(int r, int g, int b) {
            this->red = r;
            this->green = g;
            this->blue = b;
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

class Pixel {
    public:
        Color color;
        DiscretePoint pos;
        Pixel(DiscretePoint p, Color c) : color(c), pos(p) {}
};
