#include <ios>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "Datatypes.h"
#include "GraphicsObjects/Line.h"
#include "Renderer.h"
using namespace std;

int main() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    Renderer r(w.ws_col, (w.ws_row*2)-10, 10);
    int center_x = 40;
    int center_y = 40;

    Line l1(20, Point(center_x, center_y), 0, Color(213,25,125), r);
    Line l2(20, Point(center_x, center_y), 0, Color(213,25,125), r);
    r.graphics_objects.push_back(&l1);
    r.graphics_objects.push_back(&l2);

    vector<Line*> temp_lines;

    int framecount = 0;
    int position_counter = 0;
    while (true) {
        l1.transform.RotateClockwise(-0.2);
        l2.transform.RotateClockwise(0.2);
        l1.transform.SetPosition(Point(cos((float)framecount/200)*30+center_x, sin((float)framecount/200)*30+center_y));
        l2.transform.SetPosition(Point(cos((float)framecount/200)*30+center_x, sin((float)framecount/200)*30+center_y));

        for (int i = 0; i < temp_lines.size(); i++) {
            if (temp_lines[i]->color.red > 0) {
                temp_lines[i]->color.red -= 1;
                temp_lines[i]->color.green -= 1;
                temp_lines[i]->color.blue -= 1;
            }
        }

        if (framecount % 3 == 0) {
            Point new_point = l1.transform.GetPosition();
            temp_lines.push_back(new Line (1, new_point, 0, Color(255,255,255), r));
            r.graphics_objects.push_back(temp_lines[temp_lines.size()-1]);
        }

        if (temp_lines.size() > 100) {
            r.graphics_objects.erase(r.graphics_objects.begin()+2);
            delete *temp_lines.begin();
            temp_lines.erase(temp_lines.begin());
        }

        r.RasterizeGraphicsObjects();
        r.PixelBufferToTextFrame();
        r.WriteTextFrame();
        r.DrawDebugBox();
        framecount++;
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    r.RasterizeGraphicsObjects();
    r.PixelBufferToTextFrame();
    r.WriteTextFrame();
}

