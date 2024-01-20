#pragma once
#include <list>
#include <unordered_map>
#include <vector>
#include <string>
#include "Datatypes.h"
#include "Sprite.h"

class Scene {
    public:
        std::list<InputStateChange> input_queue;
        std::unordered_map<std::string, Sprite*> sprite_table;
        std::vector<std::string> sprite_keys;

        virtual void OnFrame(ProgramStateInfo program_state_info) = 0;
        void UpdateSprites(ProgramStateInfo program_state_info);
        std::vector<Pixel> RasterizeSprites();
};
