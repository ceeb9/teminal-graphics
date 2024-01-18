#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include "Scene.h"
#include "Sprite.h"

/*
 * run the onframe function of each sprite in the scene
 */
void Scene::OnFrame(ProgramStateInfo program_state_info) {
    for (int i = 0; i < sprite_keys.size(); i++) {
        if (sprite_table[sprite_keys[i]]->enabled) {
            sprite_table[sprite_keys[i]]->OnFrame(program_state_info);
        }
    }
}

/*
 * rasterize each sprite in the scene and order them (z) properly
 */
std::vector<Pixel> Scene::RasterizeSprites() {
    // rasterize each sprite, then push list of pixels onto minheap
    std::priority_queue<RasterizedSprite, std::vector<RasterizedSprite>, std::greater<RasterizedSprite>> ordered_sprites;

    for (int i = 0; i < sprite_keys.size(); i++) {
        if (sprite_table[sprite_keys[i]]->visible) {
            RasterizedSprite curr = sprite_table[sprite_keys[i]]->Rasterize();
            ordered_sprites.push(curr);
        }
    }

    // turn minheap into flat array
    std::vector<Pixel> output;

    for (int i = 0; i < sprite_keys.size(); i++) {
        RasterizedSprite current = ordered_sprites.top();

        for (int j = 0; j < current.pixels.size(); j++) {
            output.push_back(current.pixels[j]);
        }
        ordered_sprites.pop();
    }

    // todo: remove overdraw using a set
    return output;
}
