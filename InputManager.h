#pragma once
#include <list>
#include "Datatypes.h"

class InputManager {
    public:
        bool clear_input_queue;
        std::list<InputStateChange> input_queue;

        InputManager();

        void PollLoop();
};
