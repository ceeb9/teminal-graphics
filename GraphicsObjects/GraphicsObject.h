#pragma once
#include <vector>
#include "../Datatypes.h"

class GraphicsObject {
    protected:
        Transform transform;
        Color color;
    public:
        std::vector<Point> points;
        virtual std::vector<Pixel> Rasterize() = 0;
        GraphicsObject() : transform() {}
};
