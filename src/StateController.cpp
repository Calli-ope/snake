#include "headers/StateController.h"

Engine::StateController::StateController() : h_add(false), h_replace (false), h_remove(false)
{
}

Engine::StateController::~StateController()
{
}

void Engine::StateController::Add(std::unique_ptr<State> toAdd, bool replace)
{
    h_add = true;
    h_newState = std::move(toAdd);
    h_replace = replace;
}

void Engine::StateController::ProcessStateChanges()
{
    //remove the current state
    if (h_remove && !h_stateStack.empty())
    {
        h_stateStack.pop();
        if (!h_stateStack.empty())
        {
            h_stateStack.top()->Start();
        }
        h_remove = false;
    }
    //add the new state
    if (h_add)
    {
        if (h_replace && !h_stateStack.empty())
        {
            h_stateStack.pop();
            h_replace = false;
        }
        h_stateStack.push(std::move(h_newState));
        h_stateStack.top()->Init();
        h_stateStack.top()->Start();
        h_add = false;
    }
}

std::unique_ptr<Engine::State>& Engine::StateController::GetCurrent()
{
    return h_stateStack.top();
}