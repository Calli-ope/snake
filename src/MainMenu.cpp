#include "headers/MainMenu.h"
#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context> context) : m_context(context)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    m_context->m_assets->AddFont(MainFont, "assets/Baloo2.ttf");
    m_gameTitle.setFont(m_context->m_assets->GetFont(MainFont));
    m_gameTitle.setString("Snake");
}

void MainMenu::ProcessInput()
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

void MainMenu::Update(sf::Time deltaTime)
{

}

void MainMenu::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->display();
}