#pragma once
#include <vector>
#include "GraphicsObject.h"

class Line : public GraphicsObject {
    public:
        Point start;
        Point end;
        Line(Point input_start, Point input_end, Color input_color);
        std::vector<Pixel> Rasterize();
};
