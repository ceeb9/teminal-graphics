#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include "Datatypes.h"
#include "GraphicsObjects/Line.h"
#include "PixelBuffer.h"
#include "Renderer.h"
using namespace std;

int main() {
    Renderer r(80, 80, 10);
    Color c1(255, 0, 0);
    Color c2(0, 255, 0);
    Color c3(0, 0, 255);
    Color c4(255, 255, 0);

    r.pixel_buffer.SetPixel(Pixel(0, 0, c1));
    r.pixel_buffer.SetPixel(Pixel(0, 1, c2));
    r.pixel_buffer.SetPixel(Pixel(0, 2, c3));
    r.pixel_buffer.SetPixel(Pixel(0, 3, c4));

    Line l1(30, Point(40, 40), 0, Color(213,25,125), r);
    r.graphics_objects.push_back(&l1);
    while (true) {
        r.RasterizeGraphicsObjects();
        r.PixelBufferToTextFrame();
        r.WriteTextFrame();
        //r.DrawDebugBox();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        l1.transform.RotateClockwise(10);
        cout << "\x1b[1;37;40m";
        for (int i = 0; i < l1.points.size(); i++) {
            cout << "x: " << l1.points[i].x << " y: " << l1.points[i].y;
        }

    }

    r.RasterizeGraphicsObjects();
    r.PixelBufferToTextFrame();
    r.WriteTextFrame();
    //r.DrawDebugBox();
}

