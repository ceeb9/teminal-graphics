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
    private:
        Point origin;
        Point position;
        float rotation;


    public:
        std::vector<Point>* points;
        Transform(){}
        Transform(Point input_position, Point input_origin, float input_rotation, std::vector<Point>* input_points) : points(input_points) {
            this->position = input_position;
            this->origin = input_origin;
            this->rotation = input_rotation;
        }

        const Point& GetOrigin() {
            return this->origin;
        }

        const Point& GetPosition() {
            return this->position;
        }

        void SetPosition(Point new_position) {
            float offset_x = new_position.x - this->position.x;
            float offset_y = new_position.y - this->position.y;
            this->position = new_position;
            this->origin.x += offset_x;
            this->origin.y += offset_y;
            for (int i = 0; i < this->points->size(); i++) {
                (*points)[i].x += offset_x;
                (*points)[i].y += offset_y;
            }
        }

        const float& GetRotation() {
            return this->rotation;
        }

        Point RotatePointClockwise(float degrees_to_rotate, Point point_to_rotate) {
            float temp_x = point_to_rotate.x - this->origin.x;
            float temp_y = point_to_rotate.y - this->origin.y;
            float radians = degrees_to_rotate * M_PI / 180;
            float new_x = (temp_x * std::cos(radians)) - (temp_y * std::sin(radians)) + this->origin.x;
            float new_y = (temp_x * std::sin(radians)) + (temp_y * std::cos(radians)) + this->origin.y;
            if (this->rotation > 360) {
                this->rotation -= 360;
            }
            else if (this->rotation < 0) {
                this->rotation += 360;
            }
            return Point(new_x, new_y);
        }

        void RotateClockwise(float degrees_to_rotate) {
            for (int i = 0; i < points->size(); i++) {
                (*points)[i] = this->RotatePointClockwise(degrees_to_rotate, (*points)[i]);
            }
            this->rotation += degrees_to_rotate;
        }

        void SetRotation(float new_rotation) {
            float offset = new_rotation - this->rotation;
            this->RotateClockwise(offset);
        }
};
