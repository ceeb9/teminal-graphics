#include "Renderer.h"
#include <algorithm>
#include <iostream>
#include <string>
#define ANSI_RESET_COLOR "\033[1;0;49m"
#define ANSI_SET_BG_COLOR(red, green, blue) ("\033[48;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m")
#define ANSI_SET_FG_COLOR(red, green, blue) ("\033[38;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m")

void Renderer::AddPixelsToBuffer(std::vector<Pixel> pixels) {
    // reset pixel buffer to all black
    pixel_buffer = std::vector<std::vector<Color>>(SIZE_Y, std::vector<Color>(SIZE_X, Color(0, 0, 0)));

    // write pixels (if possible)
    for (int i = 0; i < pixels.size(); i++) {
        if (pixels[i].pos.y < -100 || pixels[i].pos.x < -100 || pixels[i].pos.y > SIZE_Y+100 || pixels[i].pos.x > SIZE_X+100) {
            DEBUG_BOX.AppendMessage("SOMETHING IS WRONG: tried to write pixel at x: "+std::to_string(pixels[i].pos.x)+" y: "+std::to_string(pixels[i].pos.y));
        }
        if (pixels[i].pos.x < 0 || pixels[i].pos.x >= SIZE_X) {
            //DEBUG_BOX.AppendMessage("tried to write out of bounds: (" + std::to_string(pixels[i].pos.x) + ", " + std::to_string(pixels[i].pos.y) + ")");
            continue;
        }
        if (pixels[i].pos.y < 0 || pixels[i].pos.y >= SIZE_Y) {
            //DEBUG_BOX.AppendMessage("tried to write out of bounds: (" + std::to_string(pixels[i].pos.x) + ", " + std::to_string(pixels[i].pos.y) + ")");
            continue;
        }

        pixel_buffer[pixels[i].pos.y][pixels[i].pos.x] = pixels[i].color;
    }
}

void Renderer::PixelToText() {
    std::string output = "";
    Color last_upper_color(-1,-1,-1);
    Color last_lower_color(-1,-1,-1);
    std::string last_fg_string = "";
    std::string last_bg_string = "";

    for (int y = 0; y < SIZE_Y; y+=2) {
        //output += ANSI_RESET_COLOR + std::to_string(y) + " " + last_bg_string + last_fg_string;
        for (int x = 0; x < SIZE_X; x++) {
            Color upper_pixel = pixel_buffer[y][x];
            Color lower_pixel = pixel_buffer[y+1][x];

            if (upper_pixel != last_upper_color) {
                //background (upper) color
                //std::string color_string = ANSI_SET_BG_COLOR(upper_pixel.red, upper_pixel.green, upper_pixel.blue);
                output += ANSI_SET_BG_COLOR(upper_pixel.red, upper_pixel.green, upper_pixel.blue);
                //last_bg_string = color_string;
            }

            if (lower_pixel != last_lower_color) {
                //foreground (lower) color
                //std::string color_string = ANSI_SET_FG_COLOR(lower_pixel.red, lower_pixel.green, lower_pixel.blue);
                output += ANSI_SET_FG_COLOR(lower_pixel.red, lower_pixel.green, lower_pixel.blue);
                //last_fg_string = color_string;
            }
            output += "▄";
            last_upper_color = upper_pixel;
            last_lower_color = lower_pixel;
        }
        output += "\n";
    }
    text_buffer = output;
}

void Renderer::WriteTextToScreen() {
    std::cout << ANSI_SET_CURSOR(0,0);
    //std::cout << "\n\n";
    std::cout << text_buffer;
    //std::cout << ANSI_RESET_COLOR;
}

void Renderer::RenderFromPixels(std::vector<Pixel> pixels) {
    AddPixelsToBuffer(pixels);
    PixelToText();
    WriteTextToScreen();
    framecount++;
}
