#pragma once
#include <vector>
#include "GraphicsObject.h"
#include "../Renderer.h"

class Line : public GraphicsObject {
    private:
        float length;
    public:
        Transform transform;
        Renderer& renderer;
        Line(float input_length, Point input_position, float input_rotation, Color input_color, Renderer& input_renderer);
        std::vector<Pixel> Rasterize();
};
