#include <iostream>
#include <cmath>
#include <vector>
#include "Line.h"

Line::Line(Point input_start, Point input_end, Color input_color) {
    this->start = input_start;
    this->end = input_end;
    this->color = input_color;
    // construct transform given start and end
    this->transform.position.x = (input_start.x + input_end.x) / 2;
    this->transform.position.y = (input_start.y + input_end.y) / 2;
    this->transform.origin = this->transform.position;
    this->transform.rotation = 0;
}

std::vector<Pixel> Line::Rasterize() {
    //line drawing algorithm
    std::vector<Pixel> output_pixels;
    
    // check if the line is steep (gradient > 1) if we need to do extra swapping
    float initial_gradient = (this->end.y - this->start.y) / (this->end.x - this->start.x);
    bool steep = false;
    if (std::fabs(initial_gradient) > 1) {
        steep = true;
    }

    // do a lot of swapping of coords to make sure the gradient is +-1, and goes from left to right
    float start_y = this->start.y;
    float end_y = this->end.y;
    float start_x = this->start.x;
    float end_x = this->end.x;
    if (steep) {
        std::swap(start_x, start_y);
        std::swap(end_x, end_y);
    }
    if (this->start.x > this->end.x) {
        float start_y = this->end.y;
        float end_y = this->start.y;
        float start_x = this->end.x;
        float end_x = this->start.x;
    }

    // now that swapping is done, we can get the final gradient
    float gradient = (end_y - start_y) / (end_x - start_x);

    std::cout << gradient << "\n";

    // everything has been normalized, y will only change by a max of +-1 each turn
    // go through each value of x between start and end of line, increase y by gradient each time
    // if steep, switch x and y
    float curr_y = start_y;
    for (int curr_x = floor(start_x); curr_x <= ceil(end_x); curr_x++) {
        std::cout << "x: " << curr_x << " y: " << curr_y << "\n";
        DiscretePoint curr_point = steep ? DiscretePoint(round(curr_y), curr_x) : DiscretePoint(curr_x, round(curr_y));
        output_pixels.push_back(Pixel(curr_point, Color(this->color)));
        curr_y += gradient;
    }

    return output_pixels;
}

