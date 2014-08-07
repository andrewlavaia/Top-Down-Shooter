
#include <iostream>
#include "npc.h"
#include "direction.h"

NPC::NPC(Type type)
  : type(type)
{
  distance_travelled = 0;
  directions.clear();

  switch(type)
  {
    case NPC::Goomba :
      position.x = 200;
      position.y = 200;
      speed = 4;
      weight = .5;
      distance_travelled = 0;

      directions.push_back(Direction(Direction::Down, 100));
      directions.push_back(Direction(Direction::Up, 100));
      directions.push_back(Direction(Direction::Up_Left, 50));
      directions.push_back(Direction(Direction::Up_Right, 50));
      directions.push_back(Direction(Direction::Down_Left, 50));
      directions.push_back(Direction(Direction::Down_Right, 50));
      directions.push_back(Direction(Direction::Pause, 50));
      directions.push_back(Direction(Direction::Right, 100));
      directions.push_back(Direction(Direction::Left, 100));
      break;

    case NPC::Chumba :
      position.x = 300;
      position.y = 300;
      speed = 2;
      weight = 2;
      directions.push_back(Direction(Direction::Up, 100));
      directions.push_back(Direction(Direction::Down, 100));
      break;
  }

  directions_it = directions.begin(); // intialize pointer (MUST be done after vector is populated)

}

void NPC::CreateAnimatedSprite()
{
  animatedSprite.setOrigin(16,16);
  animatedSprite.setPosition(position.x,position.y);

  // set hitbox for collision testing
  sf::Texture texture;
  texture.create(20,20);
  animatedSprite.hitbox.setTexture(texture); // aassign empty texture 20x20 pixels
  animatedSprite.hitbox.setColor(sf::Color(255,0,0,100)); // semi-transparent red hitbox
  animatedSprite.hitbox.setOrigin(10, 10);
  animatedSprite.hitbox.setPosition(position.x,position.y);

}

void NPC::CreateAnimations(const TextureManager& textures)
{
  walkAnimationDown.setSpriteSheet(textures.Get(Textures::Hero));
  walkAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
  walkAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
  walkAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
  walkAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

  walkAnimationLeft.setSpriteSheet(textures.Get(Textures::Hero));
  walkAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
  walkAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
  walkAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
  walkAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

  walkAnimationRight.setSpriteSheet(textures.Get(Textures::Hero));
  walkAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
  walkAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
  walkAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
  walkAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

  walkAnimationUp.setSpriteSheet(textures.Get(Textures::Hero));
  walkAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
  walkAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
  walkAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
  walkAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

  currentAnimation = &walkAnimationDown;
}


void NPC::MoveAnimatedSprite(double interpolation)
{
  sf::Vector2f distance = this->position - this->animatedSprite.getPosition();
  this->animatedSprite.move( distance.x * interpolation, distance.y * interpolation );
  this->animatedSprite.hitbox.setPosition(this->animatedSprite.getPosition().x, this->animatedSprite.getPosition().y);

}

