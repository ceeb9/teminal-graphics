#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "Line.h"

Line::Line(float input_length, Point input_position, float input_rotation, Color input_color, Renderer& input_renderer) : 
    renderer(input_renderer) {
    this->length = input_length;

    this->points.push_back(Point(input_position.x - length/2, input_position.y)); //start
    this->points.push_back(Point(input_position.x + length/2, input_position.y)); //end
    this->transform = Transform(input_position, input_position, 0, &this->points); // rotation is 0 so we can rotate the points properly
    this->transform.SetRotation(input_rotation);

    this->color = input_color;
}

std::vector<Pixel> Line::Rasterize() {
    // bresenham's, taken from http://members.chello.at/~easyfilter/bresenham.html
    std::vector<Pixel> output_pixels;
    int x0 = this->points[0].x;
    int y0 = this->points[0].y;
    int x1 = this->points[1].x;
    int y1 = this->points[1].y;
    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int err = dx+dy, e2; /* error value e_xy */
 
   for(;;){  /* loop */
      output_pixels.push_back(Pixel(DiscretePoint(x0, y0), color));
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }
    
    return output_pixels;
}
