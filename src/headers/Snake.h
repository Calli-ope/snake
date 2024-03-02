#pragma once

#include <list>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable
{
private:
    std::list<sf::Sprite> m_snake;
    std::list<sf::Sprite>::iterator m_head;
    std::list<sf::Sprite>::iterator m_tail;

public:
    Snake();
    ~Snake();

    void Init(const sf::Texture &texture);
    void Move(const sf::Vector2f &direction);
    bool isOn(const sf::Sprite &other) const;
    void Grow(const sf::Vector2f &direction);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
