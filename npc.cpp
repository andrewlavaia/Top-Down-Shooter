
#include <iostream>
#include "npc.h"
#include "direction.h"

NPC::NPC(Type type, const ResourceHolder<Animation, Animations::ID>& animations)
  : type(type)
{

  moveAnimation = std::make_shared<Animation>(animations.get(Animations::NPC_Run));
  attackedAnimation = moveAnimation;
  grabbedAnimation = moveAnimation;
  thrownAnimation = std::make_shared<Animation>(animations.get(Animations::Hero_Punch));
  destroyAnimation =  std::make_shared<Animation>(animations.get(Animations::Hero_Kick));

  double scale_factor = 1;
  animatedSprite.setScale(scale_factor,scale_factor);

  setCurrentAnimation(moveAnimation);
  animatedSprite.play(*getCurrentAnimation());
  animatedSprite.setLooped(false);
  animatedSprite.setFrameTime(sf::seconds(0.16));
  //sf::Color color(100,100,255);
  //animatedSprite.setColor(color);

  switch(type)
  {
    case NPC::Goomba :
      position.x = 200;
      position.y = 200;
      setSpeed(4);

      AddDirection(Orientation::S, 100, getSpeed(), false);
      //AddDirection(Orientation::NW, 100, getSpeed(), true);
      //AddDirection(Orientation::NE, 50, getSpeed(), true);
      //AddDirection(Orientation::SW, 50, getSpeed(), true);

      break;

    case NPC::Chumba :
      position.x = 300;
      position.y = 300;
      setSpeed(2);
      AddDirection(Orientation::S,  100, getSpeed(), true);
      AddDirection(Orientation::E,  100, getSpeed(), true);
      AddDirection(Orientation::NW, 100, getSpeed(), true);
      //AddDirection(Orientation::SW, 50, getSpeed(), true);
      break;
  }

  // set up AnimatedSprite
  animatedSprite.setOrigin(16,16);
  animatedSprite.setPosition(position.x,position.y);

  // set hitbox for collision testing
  animatedSprite.setHitbox(20,20);
  //animatedSprite.hitbox.setPosition(position.x,position.y);

}

void NPC::collideWithEntity(const AnimatedEntity& a, sf::Time dt)
{
  if(checkCollision(a) == false)
    return;

  if(typeid(a) == typeid(Hero))
  {
    //MoveOneUnit(a.getOrientation().getType(), 100.0, false); // This does not seem to override AI
  }
  else if(typeid(a) == typeid(NPC))
  {
    // adjust position
  }
  else if(typeid(a) == typeid(Weapon) && a.getStatus() != AnimatedEntity::Idle)
  {
    TakeDamage(a.getPower());
    std::cout<<getHP()<<std::endl;
  }
  else if(typeid(a) == typeid(Projectile))
  {
    TakeDamage(a.getPower());
    std::cout<<getHP()<<std::endl;
  }
  else if(typeid(a) == typeid(Collidable))
  {
    // adjust position, possibly take damage

  }

}
