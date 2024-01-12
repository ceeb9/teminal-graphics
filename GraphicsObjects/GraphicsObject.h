#pragma once
#include <vector>
#include "../Datatypes.h"

class GraphicsObject {
    public:
        Transform transform;
        Color color;
        virtual std::vector<Pixel> Rasterize() = 0;
};
