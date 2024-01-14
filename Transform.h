#pragma once
#include "./Datatypes.h"

class Transform {
    private:
        Point origin;
        Point position;
        float rotation;

    public:
        std::vector<Point>* points;

        Transform(){}

        Transform(Point input_position, Point input_origin, float input_rotation, std::vector<Point>* input_points);

        const Point& GetOrigin();

        const Point& GetPosition();

        void SetPosition(Point new_position);

        const float& GetRotation();

        Point RotatePointClockwise(float degrees_to_rotate, Point point_to_rotate);

        void RotateClockwise(float degrees_to_rotate);

        void SetRotation(float new_rotation);
};
