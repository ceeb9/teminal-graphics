#include <string>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Color {
    public:
        int red;
        int green;
        int blue;
        Color() {}
        Color(int input_red, int input_green, int input_blue) {
            this->red = input_red;
            this->green = input_green;
            this->blue = input_blue;
        }
};

class Point {
    public:
        float x;
        float y;
        Point(){}
        Point(float input_x, float input_y) {
            this->x = input_x;
            this->y = input_y;
        }
};

class Transform {
    public:
        Point origin;
        Point position;
        float rotation;
        Transform() {}
        Transform(Point input_origin, Point input_position, float input_rotation) {
            this->origin = input_origin;
            this->position = input_position;
            this->rotation = input_rotation;
        }
};

class Pixel {
    public:
        Point pos;
        Color color;

        Pixel(Point input_point, Color input_color) {
            this->pos = input_point;
            this->color = input_color;
        }
};

class Line {
    public:
        Transform transform;
        Color color;
        Point start;
        Point end;

        Line(Point input_start, Point input_end, Color input_color) {
            this->start = input_start;
            this->end = input_end;
            this->color = input_color;
            // construct transform given start and end
            this->transform.position.x = (input_start.x + input_end.x) / 2;
            this->transform.position.y = (input_start.y + input_end.y) / 2;
            this->transform.origin = this->transform.position;
            this->transform.rotation = 0;
        }

        vector<Pixel> Discretize() {
            //line drawing algorithm
            vector<Pixel> output_pixels;
            
            // check if the line is steep (gradient > 1) if we need to do extra swapping
            float initial_gradient = (this->end.y - this->start.y) / (this->end.x - this->start.x);
            bool steep = false;
            if (abs(initial_gradient) > 1) {
                steep = true;
            }

            // do a lot of swapping of coords to make sure the gradient is +-1, and goes from left to right
            float start_y = this->start.y;
            float end_y = this->end.y;
            float start_x = this->start.x;
            float end_x = this->end.x;
            if (steep) {
                swap(start_x, start_y);
                swap(end_x, end_y);
            }
            if (this->start.x > this->end.x) {
                float start_y = this->end.y;
                float end_y = this->start.y;
                float start_x = this->end.x;
                float end_x = this->start.x;
            }

            // now that swapping is done, we can get the final gradient
            float gradient = (end_y - start_y) / (end_x - start_x);

            cout << gradient << "\n";

            // everything has been normalized, y will only change by a max of +-1 each turn
            // go through each value of x between start and end of line, increase y by gradient each time
            // if steep, switch x and y
            float curr_y = start_y;
            for (int curr_x = floor(start_x); curr_x <= ceil(end_x); curr_x++) {
                cout << "x: " << curr_x << " y: " << curr_y << "\n";
                Point curr_point = steep ? Point(round(curr_y), curr_x) : Point(curr_x, round(curr_y));
                output_pixels.push_back(Pixel(curr_point, Color(this->color)));
                curr_y += gradient;
            }

            return output_pixels;
        }
};

class PixelBuffer {
    private:
        vector<vector<Color>> pixels;

    public:
        int SIZE_X;
        int SIZE_Y;

        PixelBuffer(int input_size_x, int input_size_y) {
            this->SIZE_X = input_size_x;
            this->SIZE_Y = input_size_y;
            this->pixels = vector<vector<Color>>(input_size_y, vector<Color>(input_size_x, Color(0, 0, 0)));
        }

        Color GetPixel(int x, int y) {
            return this->pixels[y][x];
        }

        void SetPixel(int x, int y, Color new_color) {
            this->pixels[y][x] = new_color;
        }

        string Render() {
            string output = "";
            for (int y = 0; y < this->SIZE_Y; y+=2) {
                for (int x = 0; x < this->SIZE_X; x++) {
                    
                    //background color
                    output += "\033[48;2;";
                    Color upper_pixel = this->pixels[y][x];
                    Color lower_pixel = this->pixels[y+1][x];
                    output += to_string(upper_pixel.red) + ";";
                    output += to_string(upper_pixel.green) + ";";
                    output += to_string(upper_pixel.blue) + "m";
                    
                    //foreground color
                    output += "\033[38;2;";
                    output += to_string(lower_pixel.red) + ";";
                    output += to_string(lower_pixel.green) + ";";
                    output += to_string(lower_pixel.blue) + "m";
                    output += "▄";
                }
                output += "\n";
            }

            return output;
        }
};

int main() {
    Color c1(255, 0, 0);
    Color c2(0, 255, 0);
    Color c3(0, 0, 255);
    Color c4(255, 255, 0);


    PixelBuffer pixel_buffer(80, 80);
    pixel_buffer.SetPixel(0, 0, c1);
    pixel_buffer.SetPixel(0, 1, c2);
    pixel_buffer.SetPixel(0, 2, c3);
    pixel_buffer.SetPixel(0, 3, c4);

    Line l1(Point(40,40), Point(35,72), Color(255,255,255));
    vector<Pixel> line_pixels = l1.Discretize();
    for (int i = 0; i < line_pixels.size(); i++) {
        pixel_buffer.SetPixel(line_pixels[i].pos.x, line_pixels[i].pos.y, line_pixels[i].color);
    }

    cout << "\n";
    cout << pixel_buffer.Render();
}

