#include "Transform.h"
#include <iostream>
#include <cmath>

Transform::Transform(DiscretePoint input_position, DiscretePoint input_origin, float input_rotation, std::vector<DiscretePoint>* input_points) : 
    displayed_rotation_error(0),
    position(input_position),
    origin(input_origin),
    rotation(input_rotation),
    points(input_points) {}

const DiscretePoint& Transform::GetOrigin() {
    return this->origin;
}

const DiscretePoint& Transform::GetPosition() {
    return this->position;
}

void Transform::SetPosition(DiscretePoint new_position) {
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

DiscretePoint Transform::RotatePointClockwise(float degrees_to_rotate, DiscretePoint point_to_rotate) {
    float temp_x = point_to_rotate.x - this->origin.x;
    float temp_y = point_to_rotate.y - this->origin.y;
    float radians = (degrees_to_rotate+displayed_rotation_error) * M_PI / 180;

    // perform matrix multiply to get new coords
    float new_x = (temp_x * std::cos(radians)) - (temp_y * std::sin(radians)) + this->origin.x;
    float new_y = (temp_x * std::sin(radians)) + (temp_y * std::cos(radians)) + this->origin.y;

    // clamp values
    if (this->rotation > 360) {
        this->rotation -= 360;
    }
    else if (this->rotation < 0) {
        this->rotation += 360;
    }

    // add error if points did not move
    if (std::round(new_x) == point_to_rotate.x && std::round(new_y) == point_to_rotate.y) {
        displayed_rotation_error += degrees_to_rotate;
    }

    return DiscretePoint(std::round(new_x), std::round(new_y));
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

float Transform::GetDistanceTo(DiscretePoint other_point) {
    int delta_x = other_point.x - this->position.x;
    int delta_y = other_point.y - this->position.y;
    float dist = std::sqrt(std::pow(delta_x, 2) + std::pow(delta_y, 2));
    return dist;
}
