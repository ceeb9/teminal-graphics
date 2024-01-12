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

    Line l1(Point(0,40), Point(79,40), Color(213,25,125), r);
    r.graphics_objects.push_back(&l1);
    r.RasterizeGraphicsObjects();
    r.PixelBufferToTextFrame();
    r.WriteTextFrame();
    r.DrawDebugBox();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    l1.SetPosition(Point(39.5,70));

    r.RasterizeGraphicsObjects();
    r.PixelBufferToTextFrame();
    r.WriteTextFrame();
    r.DrawDebugBox();
}

