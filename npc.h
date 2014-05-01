
#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class NPC
{
public:
  enum Type {
    Goomba,
    Chumba
  };

  explicit NPC(Type type);

  void CreateSprite(const TextureManager& textures);

  void MoveSprite(double interpolation);        // Animates sprite towards its new location based on time factor

  sf::Sprite sprite;

  sf::Vector2f position;
  double speed;
  double weight;

private:
  Type type;

};


#endif // NPC_H
