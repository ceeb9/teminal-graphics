#include <string>
#include <iostream>
#include <vector>
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

        Color get_pixel(int x, int y) {
            return this->pixels[y][x];
        }

        void set_pixel(int x, int y, Color new_color) {
            this->pixels[y][x] = new_color;
        }

        string render() {
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

    PixelBuffer pixel_buffer(4, 4);
    pixel_buffer.set_pixel(0, 0, c1);
    pixel_buffer.set_pixel(0, 1, c2);
    pixel_buffer.set_pixel(0, 2, c3);
    pixel_buffer.set_pixel(0, 3, c4);

    cout << pixel_buffer.render();
}

