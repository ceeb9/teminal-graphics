#pragma once
#include <string>
#include <vector>
#include <array>
#include "Scene.h"
#include "Renderer.h"
//#include "InputManager.h"


class SceneManager {
    private:
        std::array<Scene*, 16> scene_array;

    public:
        Renderer renderer;
        //InputManager input_manager;
        bool write_debug_info;
        int max_debug_lines;

        int active_scene_id;
        
        SceneManager(int canvas_size_x, int canvas_size_y, bool write_debug_info, int max_debug_lines);

        void AddScene(Scene* new_scene, int id);

        void MainLoop();

};
