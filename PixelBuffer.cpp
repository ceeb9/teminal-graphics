#include <string>
#include "DebugBox.h"
#include "Renderer.h"
#include "PixelBuffer.h"

void PixelBuffer::SetPixel(Pixel new_pixel) {
    bool out_of_bounds_x = new_pixel.pos.x < 0 || new_pixel.pos.x >= SIZE_X;
    bool out_of_bounds_y = new_pixel.pos.y < 0 || new_pixel.pos.y >= SIZE_Y;

    if (out_of_bounds_x || out_of_bounds_y) {
        //error
        std::string text = "Tried to write pixel out of bounds at (" + std::to_string(new_pixel.pos.x) + ", " + std::to_string(new_pixel.pos.y) + ")";
        this->renderer.debug_box.AddMessage(DebugMessageErrorLevel::WARNING, text);
    }
    else {
        this->pixels[new_pixel.pos.y][new_pixel.pos.x] = new_pixel.color;
    }
}

void PixelBuffer::SetPixels(std::vector<Pixel> new_pixels) {
    for (long unsigned int i = 0; i < new_pixels.size(); i++) {
        this->SetPixel(new_pixels[i]);
    }
}
