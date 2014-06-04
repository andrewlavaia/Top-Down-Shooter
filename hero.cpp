
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

void Hero::CreateAnimatedSprite()
{
  animatedSprite.setPosition(position.x,position.y);
}

void Hero::CreateAnimations(const TextureManager& textures)
{
  walkAnimationDown.setSpriteSheet(textures.Get(Textures::SpriteSheet));
  walkAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
  walkAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
  walkAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
  walkAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

  walkAnimationLeft.setSpriteSheet(textures.Get(Textures::SpriteSheet));
  walkAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
  walkAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
  walkAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
  walkAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

  walkAnimationRight.setSpriteSheet(textures.Get(Textures::SpriteSheet));
  walkAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
  walkAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
  walkAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
  walkAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

  walkAnimationUp.setSpriteSheet(textures.Get(Textures::SpriteSheet));
  walkAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
  walkAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
  walkAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
  walkAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

  currentAnimation = &walkAnimationRight;
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
