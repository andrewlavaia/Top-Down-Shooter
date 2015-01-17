
#include <iostream>
#include "npc.h"
#include "direction.h"

NPC::NPC(Type type, ResourceHolder<sf::Texture, Textures::ID>& texture)
  : type(type)
{

  moveAnimation = CreateAnimation(texture.get(Textures::Hero_Run), 391, 319, 12);
  attackedAnimation = moveAnimation;
  grabbedAnimation = moveAnimation;
  thrownAnimation = CreateAnimation(texture.get(Textures::Hero_Run), 391, 319, 10);

  double scale_factor = 0.10;
  animatedSprite.setScale(scale_factor,scale_factor);

  setCurrentAnimation(moveAnimation);
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

      AddDirection(Orientation::S, 100, speed, true);
      AddDirection(Orientation::NW, 100, speed, true);
      AddDirection(Orientation::NE, 50, speed, true);
      AddDirection(Orientation::SW, 50, speed, true);

      break;

    case NPC::Chumba :
      position.x = 300;
      position.y = 300;
      speed = 2;
      weight = 1;
      AddDirection(Orientation::S, 100, speed, true);
      AddDirection(Orientation::NW, 100, speed, true);
      AddDirection(Orientation::NE, 50, speed, true);
      AddDirection(Orientation::SW, 50, speed, true);
      break;
  }


  // set up AnimatedSprite
  animatedSprite.setOrigin(16,16);
  animatedSprite.setPosition(position.x,position.y);


  // set hitbox for collision testing
  sf::Texture hitbox_texture;
  hitbox_texture.create(20,20);
  animatedSprite.hitbox.setTexture(hitbox_texture); // assign empty texture 20x20 pixels
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
