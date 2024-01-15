#include <vector>
#include <iostream>
#include "DebugBox.h"
#include "Renderer.h"

void Renderer::RasterizeGraphicsObjects() {
    this->pixel_buffer.FillWithColor(Color(0,0,0));
    for (long unsigned int i = 0; i < this->graphics_objects.size(); i++) {
        if (graphics_objects[i] == nullptr) {
            this->debug_box.AddMessage(DebugMessageErrorLevel::WARNING, "tried to draw graphics object, but the pointer to it was null");
            continue;
        }
        this->pixel_buffer.SetPixels(graphics_objects[i]->Rasterize());
    }
}

void Renderer::PixelBufferToTextFrame() {
    std::vector<std::vector<Color>> pixels = this->pixel_buffer.GetPixelMatrixReference();
    std::string output = "";
    Color last_upper_color;
    Color last_lower_color;

    for (int y = 0; y < this->pixel_buffer.SIZE_Y; y+=2) {
        for (int x = 0; x < this->pixel_buffer.SIZE_X; x++) {
            Color upper_pixel = pixels[y][x];
            Color lower_pixel = pixels[y+1][x];

            if (upper_pixel != last_upper_color) {
                //background (upper) color
                output += "\033[48;2;";
                output += std::to_string(upper_pixel.red) + ";";
                output += std::to_string(upper_pixel.green) + ";";
                output += std::to_string(upper_pixel.blue) + "m";
            }

            if (lower_pixel != last_lower_color) {
                //foreground (lower) color
                output += "\033[38;2;";
                output += std::to_string(lower_pixel.red) + ";";
                output += std::to_string(lower_pixel.green) + ";";
                output += std::to_string(lower_pixel.blue) + "m";
            }
            output += "▄";
            last_upper_color = upper_pixel;
            last_lower_color = lower_pixel;
        }
        output += "\n";
    }

    this->text_frame = "\033[0;0f"+output;
}


