#pragma once
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include "GraphicsObjects/GraphicsObject.h"
#include "PixelBuffer.h"
#include "DebugBox.h"

class Renderer {
    public:
        std::vector<GraphicsObject*> graphics_objects;
        PixelBuffer pixel_buffer;
        std::string text_frame;
        DebugBox debug_box;

        Renderer(int size_x, int size_y, int debug_lines_to_show) : pixel_buffer(PixelBuffer(size_x, size_y, *this)) {
            this->text_frame = "you should never see this text, it means a text frame was never created";
            this->debug_box.lines_to_show = debug_lines_to_show;
        }
        // update the pixel buffer with newly rasterized graphics objects
        void RasterizeGraphicsObjects();

        // create the text frame from the current pixel buffer
        void PixelBufferToTextFrame();

        // write the current text frame to the screen
        void WriteTextFrame() {
            std::cout << text_frame;
        }

        // draw the debug info box
        void DrawDebugBox() {;
            std::cout << "\033[1;0;49m";
            std::cout << this->debug_box.GetVisibleLines();
        }
};
