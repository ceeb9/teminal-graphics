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
    Renderer r(90, 90, 3);
    Line l1(10, Point(79, 40), 0, Color(213,25,125), r);
    r.graphics_objects.push_back(&l1);

    std::vector<Point> positions;
    positions.push_back(Point(30, 30));
    positions.push_back(Point(60, 30));
    positions.push_back(Point(60, 60));
    positions.push_back(Point(30, 60));

    int framecount = 0;
    int position_counter = 0;
    while (true) {
        l1.transform.RotateClockwise(10);
        if (framecount % 10 == 0) {
            l1.transform.SetPosition(positions[position_counter]);
            position_counter++;
            if (position_counter == 4) {
                position_counter = 0;
            }
        }

        r.RasterizeGraphicsObjects();
        r.PixelBufferToTextFrame();
        r.WriteTextFrame();
        r.DrawDebugBox();
        framecount++;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    r.RasterizeGraphicsObjects();
    r.PixelBufferToTextFrame();
    r.WriteTextFrame();
    r.DrawDebugBox();
}

