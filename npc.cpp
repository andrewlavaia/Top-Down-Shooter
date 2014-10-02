
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
      weight = 1;

      directions.push_back(Direction(Orientation::S, 100, speed));
      directions.push_back(Direction(Orientation::N, 100, speed));
      directions.push_back(Direction(Orientation::NW, 50, speed));
      directions.push_back(Direction(Orientation::NE, 50, speed));
      directions.push_back(Direction(Orientation::SW, 50, speed));
      directions.push_back(Direction(Orientation::SE, 50, speed));
      directions.push_back(Direction(Orientation::E, 100, speed));
      directions.push_back(Direction(Orientation::W, 100, speed));
      break;

    case NPC::Chumba :
      position.x = 300;
      position.y = 300;
      speed = 2;
      weight = 1;
      directions.push_back(Direction(Orientation::N, 100, speed));
      directions.push_back(Direction(Orientation::S, 100, speed));
      directions.push_back(Direction(Orientation::NE, 100, speed, false));
      directions.push_back(Direction(Orientation::NW, 100, speed, false));
      break;
  }

  directions_it = directions.begin(); // intialize pointer (MUST be done after vector is populated)

  // set up AnimatedSprite
  animatedSprite.setOrigin(16,16);
  animatedSprite.setPosition(position.x,position.y);


  // set hitbox for collision testing
  sf::Texture texture;
  texture.create(20,20);
  animatedSprite.hitbox.setTexture(texture); // assign empty texture 20x20 pixels
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

