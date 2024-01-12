#pragma once
#include "GraphicsObjects/GraphicsObject.h"
#include "PixelBuffer.h"
#include <string>
#include <vector>


class Renderer {
    public:
        std::vector<GraphicsObject*> graphics_objects;
        PixelBuffer pixel_buffer;
        std::string text_frame;

        Renderer(int size_x, int size_y) {
            this->pixel_buffer = PixelBuffer(size_x, size_y);
            this-> text_frame = "default text";
        }
        // update the pixel buffer with newly rasterized graphics objects
        void RasterizeGraphicsObjects();

        // create the text frame from the current pixel buffer
        void PixelBufferToTextFrame();

        // write the current text frame to the screen
        void WriteTextFrame();
};
