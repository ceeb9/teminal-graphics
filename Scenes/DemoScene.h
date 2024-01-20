#pragma once
#include <chrono>
#include <string>
#include "../Renderer.h"
#include "../Sprites/SpinningLine.h"
#include "../Scene.h"

class DemoScene : public Scene {
    public:
        std::vector<SpinningLine*> lines;

        void OnFrame(ProgramStateInfo program_stat_info) override {
        }

        DemoScene() {
            srand(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
            for (int i = 0; i < 4; i++) {

                int length = std::round(10*((float)random()/(float)RAND_MAX))+4;
                DiscretePoint center = DiscretePoint(std::round(70*((float)random()/(float)RAND_MAX))+10, std::round(70*((float)random()/(float)RAND_MAX))+10);
                float rotation = 0;
                Color color = Color(std::round(255*((float)random()/(float)RAND_MAX)), std::round(255*((float)random()/(float)RAND_MAX)), std::round(255*((float)random()/(float)RAND_MAX)));
                DiscretePoint velocity = DiscretePoint(std::round(2*((float)random()/(float)RAND_MAX))+1, std::round(2*((float)random()/(float)RAND_MAX)));


                std::string key = "Line"+std::to_string(i);
                SpinningLine* new_line = new SpinningLine(key, length, center, rotation, color, velocity);

                DEBUG_BOX.AppendMessage(std::to_string(new_line->color.red)+" "+std::to_string(new_line->color.green)+" "+std::to_string(new_line->color.blue));

                lines.push_back(new_line);
                sprite_keys.push_back(key);
                sprite_table[key] = new_line;
            }
        }
};
