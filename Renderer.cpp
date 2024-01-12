#include <vector>
#include <iostream>
#include "Renderer.h"

void Renderer::RasterizeGraphicsObjects() {
    for (int i = 0; i < this->graphics_objects.size(); i++) {
        this->pixel_buffer.SetPixels(graphics_objects[i]->Rasterize());
    }
}

void Renderer::PixelBufferToTextFrame() {
    std::vector<std::vector<Color>> pixels = this->pixel_buffer.GetPixelMatrixReference();
    std::string output = "";
    for (int y = 0; y < this->pixel_buffer.SIZE_Y; y+=2) {
        for (int x = 0; x < this->pixel_buffer.SIZE_X; x++) {
            
            //background color
            output += "\033[48;2;";
            Color upper_pixel = pixels[y][x];
            Color lower_pixel = pixels[y+1][x];
            output += std::to_string(upper_pixel.red) + ";";
            output += std::to_string(upper_pixel.green) + ";";
            output += std::to_string(upper_pixel.blue) + "m";
            
            //foreground color
            output += "\033[38;2;";
            output += std::to_string(lower_pixel.red) + ";";
            output += std::to_string(lower_pixel.green) + ";";
            output += std::to_string(lower_pixel.blue) + "m";
            output += "▄";
        }
        output += "\n";
    }

    this->text_frame = output;
}

void Renderer::WriteTextFrame() {
    std::cout << "\n";
    std::cout << text_frame;
}
