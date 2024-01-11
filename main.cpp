#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Color {
    public:
        int red;
        int green;
        int blue;
        Color(int input_red, int input_green, int input_blue) {
            this->red = input_red;
            this->green = input_green;
            this->blue = input_blue;
        }
};

int main() {
    Color c1(255, 0, 0);
    Color c2(0, 255, 0);
    Color c3(0, 0, 255);
    Color c4(0, 0, 0);

    vector<vector<Color>> pixel_buffer(4, vector<Color>(4, Color(0,0,0)));
    pixel_buffer[0][0] = Color(255, 0, 0);
    pixel_buffer[0][1] = Color(0, 255, 0);
    pixel_buffer[0][2] = Color(0, 0, 255);
    pixel_buffer[0][3] = Color(255, 255, 0);

    string textframe = "";

    for (int y = 0; y < pixel_buffer.size(); y+=2) {
        for (int x = 0; x < pixel_buffer[0].size(); x++) {
            //cout << x << ", " << y << ": " << pixel_buffer[y][x].red << " " << pixel_buffer[y][x].green << " " << pixel_buffer[y][x].blue << "\n";
            
            //background color
            textframe += "\033[48;2;";
            textframe += to_string(pixel_buffer[y][x].red) + ";";
            textframe += to_string(pixel_buffer[y][x].green) + ";";
            textframe += to_string(pixel_buffer[y][x].blue) + "m";
            
            //foreground color
            textframe += "\033[38;2;";
            textframe += to_string(pixel_buffer[y+1][x].red) + ";";
            textframe += to_string(pixel_buffer[y+1][x].green) + ";";
            textframe += to_string(pixel_buffer[y+1][x].blue) + "m";
            textframe += "▄";
        }
        textframe += "\n";
    }

    cout << textframe;
}

