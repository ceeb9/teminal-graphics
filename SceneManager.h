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

        int active_scene_id;
        
        SceneManager(int canvas_size_x, int canvas_size_y);

        void AddScene(Scene* new_scene, int id);

        void MainLoop();

};
