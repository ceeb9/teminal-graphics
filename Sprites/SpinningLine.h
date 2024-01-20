#pragma once
#include "Line.h"
#include <cmath>


class SpinningLine : public Line {
    public:
        DiscretePoint velocity;
        int hit_edge_frame;
        SpinningLine(std::string input_key, float input_length, DiscretePoint center, float rotation, Color input_color, DiscretePoint velocity) : 
        Line(input_length, center, rotation, input_color), 
        velocity(velocity),
        hit_edge_frame(0){
            key = input_key;
        }

        void OnFrame(ProgramStateInfo) override;
};
