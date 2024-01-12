#pragma once
#include <vector>
#include <string>
#include "Datatypes.h"

class PixelBuffer {
    private:
        std::vector<std::vector<Color>> pixels;

    public:
        int SIZE_X;
        int SIZE_Y;

        // initialize member variables, fill internal pixel matrix with black
        PixelBuffer() {}
        PixelBuffer(int input_size_x, int input_size_y) {
            this->SIZE_X = input_size_x;
            this->SIZE_Y = input_size_y;
            this->pixels = std::vector<std::vector<Color>>(input_size_y, std::vector<Color>(input_size_x, Color(0, 0, 0)));
        }

        // get a pixel from the internal pixels matrix
        Color GetPixel(int x, int y) {
            return this->pixels[y][x];
        }

        // set a pixel in the internal pixels matrix
        void SetPixel(Pixel new_pixel) {
            this->pixels[new_pixel.pos.y][new_pixel.pos.x] = new_pixel.color;
        }

        // convenience method to set a vector of pixels
        void SetPixels(std::vector<Pixel> new_pixels) {
            for (int i = 0; i < new_pixels.size(); i++) {
                this->SetPixel(new_pixels[i]);
            }
        }

        const std::vector<std::vector<Color>>& GetPixelMatrixReference() {
            return this->pixels;
        }
};
