#include "Transform.h"

Transform::Transform(Point input_position, Point input_origin, float input_rotation, std::vector<Point>* input_points) : points(input_points) {
    this->position = input_position;
    this->origin = input_origin;
    this->rotation = input_rotation;
}

const Point& Transform::GetOrigin() {
    return this->origin;
}

const Point& Transform::GetPosition() {
    return this->position;
}

void Transform::SetPosition(Point new_position) {
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

const float& Transform::GetRotation() {
    return this->rotation;
}

Point Transform::RotatePointClockwise(float degrees_to_rotate, Point point_to_rotate) {
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

void Transform::RotateClockwise(float degrees_to_rotate) {
    for (int i = 0; i < points->size(); i++) {
        (*points)[i] = this->RotatePointClockwise(degrees_to_rotate, (*points)[i]);
    }
    this->rotation += degrees_to_rotate;
}

void Transform::SetRotation(float new_rotation) {
    float offset = new_rotation - this->rotation;
    this->RotateClockwise(offset);
}
