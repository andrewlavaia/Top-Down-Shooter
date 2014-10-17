/* TextureManager
 * --------------
 * creates an object that can load and fetch
 * a group of sf::Texture
 *
 *   usage:
 *     TextureManager textures;
 *     textures.Load(Textures::Hero, "hero.png");
 *     sf::Sprite sprite;
 *     sprite.setTexture(texture.get(Textures::Hero));
 */

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <memory>
#include <SFML/Graphics.hpp>

namespace Textures {

  enum ID {
    Hero,
    Hero2,
    NPC,
    Hitbox
  };
}

class TextureManager
{
public:
  TextureManager() {};

  void                 Load(Textures::ID id, const std::string& filename);

  sf::Texture&         Get(Textures::ID id);
  const sf::Texture&   Get(Textures::ID id) const;

private:
  std::map<Textures::ID, std::unique_ptr<sf::Texture>> texture_map;

  TextureManager(const TextureManager&);              // Disallow copy constructor
  TextureManager& operator=(const TextureManager&);   // Disallow assignment

};

#endif
