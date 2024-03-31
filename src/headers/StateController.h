#pragma once

#include <stack>
#include <memory>

#include "State.h"

namespace Engine
{
    class StateController
    {
    private:
        std::stack<std::unique_ptr<State>> h_stateStack;
        std::unique_ptr<State> h_newState;

        bool h_add;
        bool h_replace;
        bool h_remove;

    public:
        StateController();
        ~StateController();

        void Add(std::unique_ptr<State> toAdd, bool replace = false);
        void ProcessStateChanges();
        std::unique_ptr<State>& GetCurrent();
    };
}

