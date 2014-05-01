
#include "hero.h"

Hero::Hero()
{
  position.x = 50;
  position.y = 50;

  speed = 5;
  strength = 5;
}

void Hero::CreateSprite(const TextureManager& textures)
{
  sprite.setTexture(textures.Get(Textures::Hero));
  sprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
  sprite.setPosition(position.x,position.y);

}

void Hero::MoveSprite(double interpolation)
{
  // move hero sprite
  sf::Vector2f distance = this->position - this->sprite.getPosition();
  this->sprite.move( distance.x * interpolation, distance.y * interpolation );

  // choose appropriate sprite based on current direction
  if(distance.x > 1) // heading right
  {
    this->sprite.setTextureRect(sf::IntRect(40, 0, 20, 20));
  }
  else if(distance.x < -1) // heading left
  {
    this->sprite.setTextureRect(sf::IntRect(60, 0, 20, 20));
  }
  else if( distance.y > 1) // heading down
  {
    this->sprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
  }
  else if(distance.y < -1) // heading up
  {
    this->sprite.setTextureRect(sf::IntRect(20, 0, 20, 20));
  }

}
