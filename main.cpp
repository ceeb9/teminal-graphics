#include <functional>
#include <iostream>
#include <string>
#include <vector>
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
        Line* l1;

        std::function<void(ProgramStateInfo)> l1_onframe = [this](ProgramStateInfo program_state_info){
            DEBUG_BOX.AppendMessage("running l1 onframe code");
            if (program_state_info.framecount % 1 == 0) {
                if (l1->color == Color(255,255,255)) {
                    l1->color = Color(255,0,0);
                }
                else {
                    l1->color = Color(255,255,255);
                }

                l1->transform.RotateClockwise(5);
            }
        };

        DemoScene() {
            l1 = new Line(10, DiscretePoint(50,50), 0, Color(255,255,255));
            l1->OnFrame = l1_onframe;

            sprite_keys.push_back("0");
            sprite_table["0"] = l1;
        }
};

int main() {
    DemoScene test_scene;
    SceneManager manager(100, 100);
    manager.AddScene(&test_scene, 0);
    manager.active_scene_id = 0;
    manager.MainLoop();
}
