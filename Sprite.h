#pragma once
#include <functional>
#include "Datatypes.h"
#include "Transform.h"
#include <string>
#include <tuple>
#include <vector>

class RasterizedSprite {
    public:
        std::vector<Pixel> pixels;
        int z_index;

        RasterizedSprite(std::vector<Pixel> p, int z) {
            pixels = p;
            z_index = z;
        }

        bool operator>(const RasterizedSprite& other) const {
            if (this->z_index > other.z_index) {
                return true;
            }
            else {
                return false;
            }
        }
};

/**
 * a base class for user created sprites to inherit from
 */
class Sprite {
    public:
        bool enabled;
        bool visible;
        std::string key;
        Transform transform;

        virtual void OnFrame(ProgramStateInfo program_state_info) = 0;

        virtual RasterizedSprite Rasterize() = 0;
};

