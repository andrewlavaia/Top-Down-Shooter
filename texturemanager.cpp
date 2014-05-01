
#include "texturemanager.h"

  void TextureManager::Load(Textures::ID id, const std::string& filename)
  {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromFile(filename);

    texture_map.insert(std::make_pair(id, std::move(texture)));
  }

  sf::Texture& TextureManager::Get(Textures::ID id)
  {
    auto found = texture_map.find(id);
    return *found->second;
  }

  const sf::Texture& TextureManager::Get(Textures::ID id) const
  {
    auto found = texture_map.find(id);
    return *found->second;
  }
