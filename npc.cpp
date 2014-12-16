
#include <iostream>
#include "npc.h"
#include "direction.h"

NPC::NPC(Type type)
  : type(type)
{

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

  /*
  walkAnimationDown.setSpriteSheet(textures.Get(Textures::NPC));
  walkAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
  walkAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
  walkAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
  walkAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

  walkAnimationLeft.setSpriteSheet(textures.Get(Textures::NPC));
  walkAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
  walkAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
  walkAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
  walkAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

  walkAnimationRight.setSpriteSheet(textures.Get(Textures::NPC));
  walkAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
  walkAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
  walkAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
  walkAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

  walkAnimationUp.setSpriteSheet(textures.Get(Textures::NPC));
  walkAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
  walkAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
  walkAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
  walkAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));
  */


  // assign animations based on NPC type

  defaultAnimation = CreateAnimation(textures.Get(Textures::Hero_Run), 391, 319, 12);
  attackedAnimation = defaultAnimation;
  grabbedAnimation = defaultAnimation;
  thrownAnimation = defaultAnimation;

  double scale_factor = 0.10;
  animatedSprite.setScale(scale_factor,scale_factor);

  currentAnimation = &defaultAnimation;
  animatedSprite.play(*currentAnimation);
  animatedSprite.setLooped(true);
  animatedSprite.setFrameTime(sf::seconds(0.16));
  sf::Color color(100,100,255);
  animatedSprite.setColor(color);
}
/*
Animation NPC::CreateAnimation(const sf::Texture& tex, unsigned width, unsigned height, unsigned sprite_count)
{
  Animation animation;
  animation.setSpriteSheet(tex);
  for (unsigned i = 0; i < sprite_count; ++i)
  {
    animation.addFrame(sf::IntRect( i * width, 0, width,  height));
  }

  return animation;
}


void NPC::MoveAnimatedSprite(double interpolation)
{
  animatedSprite.setOrigin(animatedSprite.getLocalBounds().width/2, animatedSprite.getLocalBounds().height/2);
  sf::Vector2f distance = this->position - this->animatedSprite.getPosition();
  this->animatedSprite.move( distance.x * interpolation, distance.y * interpolation );
  this->animatedSprite.hitbox.setPosition(this->animatedSprite.getPosition().x, this->animatedSprite.getPosition().y);
}

void NPC::MoveOppo(double d)
{
  Orientation o;
  o.setType(directions_it->getType());
  directions_it = directions.insert(directions_it + 1,
                                    Direction(o.getOppo(),d,directions_it->getSpeed(),false));
  distance_travelled = 0;
}
*/
