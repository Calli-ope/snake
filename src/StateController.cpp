#include "headers/StateController.h"

Engine::StateController::StateController() : m_add(false), m_replace (false), m_remove(false)
{
}

Engine::StateController::~StateController()
{
}

void Engine::StateController::Add(std::unique_ptr<State> toAdd, bool replace)
{
    m_add = true;
    m_newState = std::move(toAdd);
    m_replace = replace;
}

void Engine::StateController::PopCurrent()
{
    m_remove = true;
}

void Engine::StateController::ProcessStateChanges()
{
    if (m_remove && !m_stateStack.empty())
    {
        m_stateStack.pop();
        if (!m_stateStack.empty())
        {
            m_stateStack.top()->Start();
        }
        m_remove = false;
    }
    if (m_add)
    {
        if (m_replace && !m_stateStack.empty())
        {
            m_stateStack.pop();
            m_replace = false;
        }
        if (!m_stateStack.empty())
        {
            m_stateStack.top()->Pause();
        }
        m_stateStack.push(std::move(m_newState));
        m_stateStack.top()->Init();
        m_stateStack.top()->Start();
        m_add = false;
    }
}

std::unique_ptr<Engine::State>& Engine::StateController::GetCurrent()
{
    return m_stateStack.top();
}