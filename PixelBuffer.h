#pragma once
#include <vector>
#include <string>
#include "Datatypes.h"
//#include "Renderer.h"

// forward definition because we need a reference to the renderer in the definition
class Renderer;

class PixelBuffer {
    private:
        std::vector<std::vector<Color>> pixels;

    public:
        int SIZE_X;
        int SIZE_Y;
        Renderer& renderer;

        // initialize member variables, fill internal pixel matrix with black
        PixelBuffer(int input_size_x, int input_size_y, Renderer& input_renderer) : renderer(input_renderer) {
            this->SIZE_X = input_size_x;
            this->SIZE_Y = input_size_y;
            this->pixels = std::vector<std::vector<Color>>(input_size_y, std::vector<Color>(input_size_x, Color(0, 0, 0)));
        }

        void FillWithColor(Color color) {
            this->pixels = std::vector<std::vector<Color>>(this->SIZE_Y, std::vector<Color>(this->SIZE_X, color));
        }

        // get a pixel from the internal pixels matrix
        Color GetPixel(int x, int y) {
            return this->pixels[y][x];
        }

        // set a pixel in the internal pixels matrix
        void SetPixel(Pixel new_pixel);

        // convenience method to set a vector of pixels
        void SetPixels(std::vector<Pixel> new_pixels);

        const std::vector<std::vector<Color>>& GetPixelMatrixReference() {
            return this->pixels;
        }
};
