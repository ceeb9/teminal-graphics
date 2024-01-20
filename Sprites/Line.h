#pragma once
#include "../Sprite.h"

class Line : public Sprite {
    public:
        std::vector<DiscretePoint> points;
        Color color;
        float length;

        Line(float input_length, DiscretePoint center, float rotation, Color input_color) { 
            enabled = true;
            visible = true;
            length = input_length;
            color = input_color;
            points.push_back(DiscretePoint(center.x - length/2, center.y)); //start
            points.push_back(DiscretePoint(center.x + length/2, center.y)); //end
            transform = Transform(center, center, 0, &this->points); // rotation is 0 so we can rotate the points properly
            transform.SetRotation(rotation);
        }

        RasterizedSprite Rasterize() override {
            // bresenham's, taken from http://members.chello.at/~easyfilter/bresenham.html
            std::vector<Pixel> output_pixels;
            int x0 = this->points[0].x;
            int y0 = this->points[0].y;
            int x1 = this->points[1].x;
            int y1 = this->points[1].y;
            int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
            int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
            int err = dx+dy, e2; /* error value e_xy */

            for(;;) {  /* loop */
                output_pixels.push_back(Pixel(DiscretePoint(x0, y0), color));
                if (x0==x1 && y0==y1) break;
                e2 = 2*err;
                if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
                if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
            }

            return RasterizedSprite(output_pixels, 0);
        }
        
        void OnFrame(ProgramStateInfo program_state_info) override {};
};
