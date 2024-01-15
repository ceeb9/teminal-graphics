#pragma once
#include <vector>
#include "../Datatypes.h"
#include "../Transform.h"

class GraphicsObject {
    protected:
        Transform transform;
    public:
        Color color;
        std::vector<Point> points;
        virtual std::vector<Pixel> Rasterize() = 0;
        GraphicsObject() : transform() {}
};
