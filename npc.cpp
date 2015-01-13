
#include <iostream>
#include "npc.h"
#include "direction.h"

NPC::NPC(Type type, TextureManager& texture)
  : type(type)
{

  defaultAnimation = CreateAnimation(texture.Get(Textures::Hero_Run), 391, 319, 12);
  attackedAnimation = defaultAnimation;
  grabbedAnimation = defaultAnimation;
  thrownAnimation = defaultAnimation;

  double scale_factor = 0.10;
  animatedSprite.setScale(scale_factor,scale_factor);

  setCurrentAnimation(defaultAnimation);
  animatedSprite.play(*getCurrentAnimation());
  animatedSprite.setLooped(true);
  animatedSprite.setFrameTime(sf::seconds(0.16));
  sf::Color color(100,100,255);
  animatedSprite.setColor(color);

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
  sf::Texture tex;
  tex.create(20,20);
  animatedSprite.hitbox.setTexture(tex); // assign empty texture 20x20 pixels
  animatedSprite.hitbox.setColor(sf::Color(255,0,0,100)); // semi-transparent red hitbox
  animatedSprite.hitbox.setOrigin(10, 10);
  animatedSprite.hitbox.setPosition(position.x,position.y);

}

void NPC::collideWithEntity(const AnimatedEntity& a)
{
  if (checkCollision(a) == false)
    return;

  if(typeid(a) == typeid(Hero))
  {
    //  adjust position
  }
  else if(typeid(a) == typeid(NPC))
  {
    // adjust position
  }
  else if(typeid(a) == typeid(Weapon))
  {
    // take damage
  }
  else if(typeid(a) == typeid(Projectile))
  {
    // take damage
  }
  else if(typeid(a) == typeid(Collidable))
  {
    // adjust position, possibly take damage

  }

}
