
#include <iostream>
#include "npc.h"

NPC::NPC()
{
  position.x = 200;
  position.y = 200;

  if (!texture.loadFromFile("character-sprite-map.gif"))
  {
    std::cout << "texture loading error" << std::endl;
  }
  texture.setSmooth(true);

  sprite.setTexture(texture,true);
  sprite.setTextureRect(sf::IntRect(167, 20, 20, 20));
  sprite.setPosition(position.x,position.y);

  speed = 1;
  weight = .5;

}

void NPC::MoveSprite(double interpolation)
{
  sf::Vector2f distance = this->position - this->sprite.getPosition();
  this->sprite.move( distance.x * interpolation, distance.y * interpolation );
}
