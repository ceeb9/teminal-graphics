#pragma once
#include <vector>
#include "GraphicsObject.h"
#include "../Renderer.h"

class Line : public GraphicsObject {
    public:
        Renderer& renderer;
        Point start;
        Point end;
        Line(Point input_start, Point input_end, Color input_color, Renderer& input_renderer);
        std::vector<Pixel> Rasterize();
};
