#include "headers/Snake.h"

Snake::Snake() : m_snake(std::list<sf::Sprite>(4))
{
    m_head = --m_snake.end();
    m_tail = m_snake.begin();
}

Snake::~Snake()
{
}

void Snake::Init(const sf::Texture &texture)
{
    float x = 16.f;
    for (auto &segment : m_snake)
    {
        segment.setTexture(texture);
        segment.setPosition(x, 16.f);
        x += 16.f;
    }
}

void Snake::Move(const sf::Vector2f &direction)
{
    m_tail->setPosition(m_head->getPosition() + direction);
    m_head = m_tail;
    m_tail++;

    if (m_tail == m_snake.end())
    {
        m_tail = m_snake.begin();
    }
}

bool Snake::isOn(const sf::Sprite &other) const
{
}

void Snake::Grow(const sf::Vector2f &direction)
{

}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &segment : m_snake)
    {
        target.draw(segment);
    }
}