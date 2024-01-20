#include "Scenes/DemoScene.h"
#include "SceneManager.h"

int main() {
    DemoScene test_scene;
    SceneManager manager(90, 90, true, 40);
    manager.AddScene(&test_scene, 0);
    manager.active_scene_id = 0;
    manager.MainLoop();
}
