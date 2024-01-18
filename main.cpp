#include <bits/chrono.h>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <cmath>
#include "Datatypes.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Scene.h"
#include "SceneManager.h"

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

        RasterizedSprite Rasterize() {
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
};

class DemoScene : public Scene {
    public:
        std::vector<Line*> lines;
        Line* l1;
        Line* l2;

        std::function<void(ProgramStateInfo)> GenerateLineOnFrame(Line* line, DiscretePoint* velocity, Color* c, int* hit_edge_frame) {
            return [line, velocity, c, hit_edge_frame, this](ProgramStateInfo program_state_info){
                //DEBUG_BOX.AppendMessage("onframe code received info: framecount="+std::to_string(program_state_info.framecount)+
                //        ", size_x="+std::to_string(program_state_info.canvas_size_x)+", size_y="+std::to_string(program_state_info.canvas_size_y));
                line->transform.RotateClockwise(1);

                int curr_x = line->transform.GetPosition().x;
                int curr_y = line->transform.GetPosition().y;
                //DEBUG_BOX.AppendMessage("x: " + std::to_string(curr_x) + " y:" + std::to_string(curr_y));

                //DEBUG_BOX.AppendMessage("hit edge " + std::to_string(*hit_edge_frame) + " frames ago");
                if (*hit_edge_frame < 3) {
                    //line->color.red = 255;
                    //line->color.blue = 255;
                    //line->color.green = 255;
                    (*hit_edge_frame)++;
                    line->color = Color(std::round(255*((float)random()/(float)RAND_MAX)), std::round(255*((float)random()/(float)RAND_MAX)), std::round(255*((float)random()/(float)RAND_MAX)));
                }
                else {
                    *hit_edge_frame = 4;
                    line->color.red = c->red;
                    line->color.blue = c->blue;
                    line->color.green = c->green;
                    //DEBUG_BOX.AppendMessage("r: "+std::to_string(c->red)+" g: "+std::to_string(c->green)+" b: "+std::to_string(c->blue));
                }

                if (curr_x < 2 || curr_x > program_state_info.canvas_size_x-2) {
                    velocity->x = velocity->x*-1;
                    *hit_edge_frame = 0;
                    //DEBUG_BOX.AppendMessage("hit edge on x");
                }

                if (curr_y < 2 || curr_y > program_state_info.canvas_size_y-2) {
                    velocity->y = velocity->y*-1;
                    *hit_edge_frame = 0;
                    //DEBUG_BOX.AppendMessage("hit edge on y");
                }
                
                line->transform.SetPosition(DiscretePoint(curr_x+velocity->x, curr_y+velocity->y));
            };
        };

        DemoScene() {
            srand(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
            for (int i = 0; i < 100; i++) {

                Color* new_color = new Color(std::round(255*((float)random()/(float)RAND_MAX)), std::round(255*((float)random()/(float)RAND_MAX)), std::round(255*((float)random()/(float)RAND_MAX)));
                Line* new_line = new Line(std::round(10*((float)random()/(float)RAND_MAX))+4, DiscretePoint(std::round(70*((float)random()/(float)RAND_MAX))+10, std::round(70*((float)random()/(float)RAND_MAX))+10), 0, *new_color);
                DiscretePoint* new_direction = new DiscretePoint(std::round(5*((float)random()/(float)RAND_MAX))+1, std::round(5*((float)random()/(float)RAND_MAX)));

                //DEBUG_BOX.AppendMessage(std::to_string(new_color->red)+" "+std::to_string(new_color->green)+" "+std::to_string(new_color->blue));

                new_line->OnFrame = GenerateLineOnFrame(new_line, new_direction, new_color, new int(100));

                lines.push_back(new_line);
                sprite_keys.push_back("Line"+std::to_string(i));
                sprite_table["Line"+std::to_string(i)] = new_line;
            }
        }
};

int main() {
    DemoScene test_scene;
    SceneManager manager(90, 90, true, 40);
    manager.AddScene(&test_scene, 0);
    manager.active_scene_id = 0;
    manager.MainLoop();
}
