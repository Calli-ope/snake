#include "headers/GamePlay.h"

GamePlay::GamePlay(std::shared_ptr<Context>& context)
    : m_context(context)
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    m_context->m_assets->AddTexture(Background, "assets/background.png", true);

    m_background.setTexture(m_context->m_assets->GetTexture(Background));
    m_background.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
}

void GamePlay::ProcessInput()
{

}

void GamePlay::Update(sf::Time deltaTime)
{

}

void GamePlay::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_background);
    m_context->m_window->display();
}

void GamePlay::Pause()
{

}

void GamePlay::Start()
{

}