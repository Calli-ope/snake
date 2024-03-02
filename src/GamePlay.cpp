#include "headers/GamePlay.h"
#include <SFML/Window/Event.hpp>

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
    m_context->m_assets->AddTexture(Border, "assets/border.png", true);
    m_context->m_assets->AddTexture(Food, "assets/food.png");
    m_context->m_assets->AddTexture(Snake, "assets/snake.png");

    //display background
    m_background.setTexture(m_context->m_assets->GetTexture(Background));
    m_background.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    //display border
    for (auto& border : m_border)
    {
        border.setTexture(m_context->m_assets->GetTexture(Border));
    }

    m_border[0].setTextureRect({0, 0, m_context->m_window->getSize().x, 16});
    m_border[1].setTextureRect({0, 0, m_context->m_window->getSize().x, 16});
    m_border[1].setPosition(0, m_context->m_window->getSize().y - 16);

    m_border[2].setTextureRect({0, 0, 16, m_context->m_window->getSize().y});
    m_border[3].setTextureRect({0, 0, 16, m_context->m_window->getSize().y});
    m_border[3].setPosition(m_context->m_window->getSize().x - 16, 0);

    //display food
    m_food.setTexture(m_context->m_assets->GetTexture(Food));
    m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
    }
}

void GamePlay::Update(sf::Time deltaTime)
{

}

void GamePlay::Draw()
{
    m_context->m_window->clear();

    m_context->m_window->draw(m_background);
    for (auto& border : m_border)
    {
        m_context->m_window->draw(border);
    }
    m_context->m_window->draw(m_food);

    m_context->m_window->display();
}

void GamePlay::Pause()
{

}

void GamePlay::Start()
{

}