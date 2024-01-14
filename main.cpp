#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include "Datatypes.h"
#include "GraphicsObjects/Line.h"
#include "Renderer.h"
using namespace std;

int main() {
    Renderer r(250, 250, 3);
    int center = 250/2;
    Line l1(50, Point(center, center), 0, Color(213,25,125), r);
    Line l2(50, Point(center, center), 0, Color(213,25,125), r);
    r.graphics_objects.push_back(&l1);
    r.graphics_objects.push_back(&l2);

    vector<Line> temp_lines;

    int framecount = 0;
    int position_counter = 0;
    while (true) {
        l1.transform.RotateClockwise(-1);
        l2.transform.RotateClockwise(1);
        l1.transform.SetPosition(Point(cos((float)framecount/32)*75+center, sin((float)framecount/32)*75+center));
        l2.transform.SetPosition(Point(cos((float)framecount/32)*75+center, sin((float)framecount/32)*75+center));

        if (framecount % 3 == 0) {
            Point new_point = l1.transform.GetPosition();
            r.graphics_objects.push_back(new Line (1, new_point, 0, Color(255,255,255), r));
        }

        r.RasterizeGraphicsObjects();
        r.PixelBufferToTextFrame();
        r.WriteTextFrame();
        r.DrawDebugBox();
        framecount++;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    r.RasterizeGraphicsObjects();
    r.PixelBufferToTextFrame();
    r.WriteTextFrame();
}

