#pragma once

#include <stack>
#include <memory>

#include "State.h"

namespace Engine
{
    class StateController
    {
    private:
        std::stack<std::unique_ptr<State>> m_stateStack;
        std::unique_ptr<State> m_newState;

        bool m_add;
        bool m_replace;
        bool m_remove;

    public:
        StateController();
        ~StateController();

        void Add(std::unique_ptr<State> toAdd, bool replace = false);
        void PopCurrent();
        void ProcessStateChanges();
        std::unique_ptr<State>& GetCurrent();
    };
}

