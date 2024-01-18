#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Datatypes.h"
#define ANSI_RESET_COLOR "\033[1;0;49m"
#define ANSI_SET_CURSOR(x, y) ("\033[" + std::to_string(y) + ";" + std::to_string(x) + "H")
#define DEBUG_BOX DebugBox::GetInstance()

class Renderer {
    private:
        int SIZE_X;
        int SIZE_Y;
        int framecount;

        std::vector<std::vector<Color>> pixel_buffer;
        std::string text_buffer;

        void AddPixelsToBuffer(std::vector<Pixel> pixels);
        void PixelToText();
        void WriteTextToScreen();
    public:
        Renderer(int size_x, int size_y) {
            SIZE_X = size_x;
            SIZE_Y = size_y;
            framecount = 0;
            this->pixel_buffer = std::vector<std::vector<Color>>(size_y, std::vector<Color>(size_x, Color(0, 0, 0)));
        }

        void RenderFromPixels(std::vector<Pixel> pixels);

        int GetWidth() {
            return this->SIZE_X;
        }

        int GetHeight() {
            return this->SIZE_Y;
        }

        int GetFramecount() {
            return this->framecount;
        }
};

class DebugBox {
    private:
        // private constructor, delete assignment and copy constructor to enforce singleton
        DebugBox() {}
        DebugBox(const DebugBox&) = delete;
        DebugBox& operator=(const DebugBox&) = delete;
        int times_displayed = 0;

        std::vector<std::string> messages;

    public:
        // instantiates on first run, then returns the same
        static DebugBox& GetInstance() {
            static DebugBox instance;
            return instance;
        }

        void AppendMessage(std::string message) {
            messages.push_back("[" + std::to_string(times_displayed) + "] " + message);
        }

        void DisplayMessages(int max_lines, int x) {
            times_displayed += 1;
            int lines_to_print = messages.size();
            if (messages.size() > max_lines) {
                lines_to_print = max_lines+1;
            }

            std::cout << ANSI_RESET_COLOR;
            for (int i = 0; i < lines_to_print; i++) {
                std::cout << ANSI_SET_CURSOR(x, i);
                std::cout << messages[messages.size()-1-i] + "\n";
            }
        }
};
