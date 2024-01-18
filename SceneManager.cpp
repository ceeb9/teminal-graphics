#include <iostream>
#include "SceneManager.h"
#include "Datatypes.h"
#include "InputManager.h"
#include "Scene.h"
#include <chrono>
#include <thread>

SceneManager::SceneManager(int canvas_size_x, int canvas_size_y, bool i_write_debug_info, int i_max_debug_lines) : 
    renderer(Renderer(canvas_size_x, canvas_size_y))
    //input_manager() 
    {
        this->write_debug_info = i_write_debug_info;
        this->max_debug_lines = i_max_debug_lines;
    }

void SceneManager::AddScene(Scene* new_scene, int id) {
    this->scene_array[id] = new_scene;
} 

void SceneManager::MainLoop() {
    std::cout << "\e[?25l";
    while (true) {
        // get program state info to send to sprites
        ProgramStateInfo curr_psi;
        //curr_psi.input_queue = input_manager.input_queue;
        //input_manager.clear_input_queue = true;

        curr_psi.canvas_size_x = renderer.GetWidth();
        curr_psi.canvas_size_y = renderer.GetHeight();
        curr_psi.framecount = renderer.GetFramecount();

        // update sprite states
        scene_array[active_scene_id]->OnFrame(curr_psi);

        // get the pixels to render
        std::vector<Pixel> pixels = scene_array[active_scene_id]->RasterizeSprites();
        renderer.RenderFromPixels(pixels);

        // print debug box
        if (write_debug_info) {
            DEBUG_BOX.DisplayMessages(max_debug_lines, renderer.GetWidth()+2);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    std::cout << "\e[?25h";
}
