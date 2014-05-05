
#include <iostream>
#include "npc.h"

NPC::NPC(Type type)
  : type(type)
{
  if(type == NPC::Goomba) {
    position.x = 200;
    position.y = 200;
    speed = 1;
    weight = .5;
  }
  if(type == NPC::Chumba) {
    position.x = 300;
    position.y = 300;
    speed = 1;
    weight = 2;
  }
}

void NPC::CreateSprite(const TextureManager& textures)
{
  sprite.setTexture(textures.Get(Textures::Hero));
  sprite.setTextureRect(sf::IntRect(167, 20, 20, 20));
  sprite.setPosition(position.x,position.y);
}

void NPC::MoveSprite(double interpolation)
{
  sf::Vector2f distance = this->position - this->sprite.getPosition();
  this->sprite.move( distance.x * interpolation, distance.y * interpolation );
}
