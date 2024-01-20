#pragma once
#include "Datatypes.h"
#include <vector>

class Transform {
    private:
        DiscretePoint position;
        int z_index;
        DiscretePoint origin;
        float rotation;
        float displayed_rotation_error;

    public:
        std::vector<DiscretePoint>* points;

        Transform(){}

        Transform(DiscretePoint input_position, DiscretePoint input_origin, float input_rotation, std::vector<DiscretePoint>* input_points);

        const DiscretePoint& GetOrigin();

        const DiscretePoint& GetPosition();

        void SetPosition(DiscretePoint new_position);

        const float& GetRotation();

        DiscretePoint RotatePointClockwise(float degrees_to_rotate, DiscretePoint point_to_rotate);

        void RotateClockwise(float degrees_to_rotate);

        void SetRotation(float new_rotation);

        float GetDistanceTo(DiscretePoint other_point);
};
