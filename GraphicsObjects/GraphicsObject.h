#pragma once
#include <vector>
#include "../Datatypes.h"

class GraphicsObject {
    protected:
        Transform transform;
        Color color;
    public:
        virtual std::vector<Pixel> Rasterize() = 0;

        virtual void SetPosition(Point new_position) = 0;

        Point GetPosition() {
            return this->transform.position;
        }
};
