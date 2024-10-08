#include "headers/AssetManager.h"

Engine::AssetManager::AssetManager()
{
}

Engine::AssetManager::~AssetManager()
{
}

void Engine::AssetManager::AddTexture(int id, const std::string& filePath, bool needRepeated)
{
    //create a new texture and load it from file
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(filePath))
    {
        texture->setRepeated(needRepeated);
        h_textures[id] = std::move(texture);
    }
}

void Engine::AssetManager::AddFont(int id, const std::string& filePath)
{
    //create a new font and load it from file
    auto font = std::make_unique<sf::Font>();

    if (font->loadFromFile(filePath))
    {
        h_fonts[id] = std::move(font);
    }
}

const sf::Texture &Engine::AssetManager::GetTexture(int id) const
{
    return *(h_textures.at(id).get());
}

const sf::Font &Engine::AssetManager::GetFont(int id) const
{
    return *(h_fonts.at(id).get());
}