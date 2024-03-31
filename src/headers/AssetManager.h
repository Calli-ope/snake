#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Engine
{
    class AssetManager
    {
    private:
        std::map<int, std::unique_ptr<sf::Texture>> h_textures;
        std::map<int, std::unique_ptr<sf::Font>> h_fonts;

    public:
        AssetManager();
        ~AssetManager();

        void AddTexture(int id, const std::string &filePath, bool needRepeated = false);
        void AddFont(int id, const std::string &filePath);

        const sf::Texture &GetTexture(int id) const;
        const sf::Font &GetFont(int id) const;
    };
}