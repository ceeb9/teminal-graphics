#include <iostream>
#include "SceneManager.h"
#include "Datatypes.h"
#include "InputManager.h"
#include "Scene.h"
#include <chrono>
#include <thread>

SceneManager::SceneManager(int canvas_size_x, int canvas_size_y) : 
    renderer(Renderer(canvas_size_x, canvas_size_y))
    //input_manager() 
    {}

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
        curr_psi.canvas_size_x = renderer.GetHeight();
        curr_psi.framecount = renderer.GetFramecount();

        // update sprite states
        scene_array[active_scene_id]->OnFrame(curr_psi);

        // get the pixels to render
        std::vector<Pixel> pixels = scene_array[active_scene_id]->RasterizeSprites();
        renderer.RenderFromPixels(pixels);

        // print debug box
        DEBUG_BOX.DisplayMessages(10, renderer.GetWidth()+4);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "\e[?25h";
}
