
#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Hero
{
public:
  Hero();

  void CreateSprite(const TextureManager& textures);

  void MoveSprite(double interpolation);   // Animates sprite towards its new location based on time factor

  sf::Vector2f position;

  sf::Sprite sprite;

  double speed;
  double strength;


private:


};



#endif // HERO_H
