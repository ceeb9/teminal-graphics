#include "../Scenes/DemoScene.h"
#include "SpinningLine.h"
#include <string>

void SpinningLine::OnFrame(ProgramStateInfo program_state_info) {
    //DEBUG_BOX.AppendMessage("onframe code received info: framecount="+std::to_string(program_state_info.framecount)+
    //        ", size_x="+std::to_string(program_state_info.canvas_size_x)+", size_y="+std::to_string(program_state_info.canvas_size_y));
    transform.RotateClockwise(1);

    int curr_x = transform.GetPosition().x;
    int curr_y = transform.GetPosition().y;
    //DEBUG_BOX.AppendMessage("x: " + std::to_string(curr_x) + " y:" + std::to_string(curr_y));

    DEBUG_BOX.AppendMessage(std::to_string(hit_edge_frame));
    if (hit_edge_frame <= 7) {
        color.red = 255;
        color.blue = 255;
        color.green = 255;
        (hit_edge_frame)++;
    }
    else if (hit_edge_frame == 8) {
        color = Color(std::round(255*((float)random()/(float)RAND_MAX)), std::round(255*((float)random()/(float)RAND_MAX)), std::round(255*((float)random()/(float)RAND_MAX)));
        hit_edge_frame++;
    }
    else if (hit_edge_frame > 8){
        hit_edge_frame = 9;
        //DEBUG_BOX.AppendMessage("r: "+std::to_string(c->red)+" g: "+std::to_string(c->green)+" b: "+std::to_string(c->blue));
    }

    if (curr_x < 2 || curr_x > program_state_info.canvas_size_x-2) {
        velocity.x = velocity.x*-1;
        //hit_edge_frame = 0;
        //DEBUG_BOX.AppendMessage("hit edge on x");
    }

    if (curr_y < 2 || curr_y > program_state_info.canvas_size_y-2) {
        velocity.y = velocity.y*-1;
        //hit_edge_frame = 0;
        //DEBUG_BOX.AppendMessage("hit edge on y");
    }

    DemoScene* scene = dynamic_cast<DemoScene*>(program_state_info.scene);

    for (int i = 0; i < scene->sprite_keys.size(); i++) {
        SpinningLine* other = dynamic_cast<SpinningLine*>(scene->sprite_table[scene->sprite_keys[i]]);
        if (other->key == key) {
            continue;
        }

        float distance = transform.GetDistanceTo(other->transform.GetPosition());
        //DEBUG_BOX.AppendMessage(std::to_string(distance));
        if (distance < (float)(length + other->length)/(float)2) {
            DEBUG_BOX.AppendMessage("touched other line");
            hit_edge_frame = 0;
        }
    }
    
    transform.SetPosition(DiscretePoint(curr_x+velocity.x, curr_y+velocity.y));
}
