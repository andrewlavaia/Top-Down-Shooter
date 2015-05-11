
#include "npc.h"
#include "datatables.h"

namespace
{
  //const std::vector<NPCData> Table = initializeNPCData();
}

NPC::NPC(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data, double x, double y)
  : AnimatedEntity(AnimatedEntity::NPCType),
    type(t),
    idleAnimation(animations.get(Animations::NPC_Run)),
    moveAnimation(animations.get(Animations::NPC_Run)),
    dieAnimation(animations.get(Animations::NPC_Run)),
    deadAnimation(animations.get(Animations::NPC_Run)),
    attackedAnimation(animations.get(Animations::NPC_Run)),
    grabbedAnimation(animations.get(Animations::NPC_Run)),
    thrownAnimation(animations.get(Animations::NPC_Run))
{
  position.x = x;
  position.y = y;

  //std::cout<<Table[t].hitpoints<<std::endl;

  setStatus(AnimatedEntity::Moving);
  playAnimation();
  animatedSprite.setFrameTime(sf::seconds(0.16));
  animatedSprite.setScale(1,1);

  //double scale_factor = 1;


  //animatedSprite.setAnimation(moveAnimation);
  //animatedSprite.play(moveAnimation);
  //setCurrentAnimation(moveAnimation);
  //animatedSprite.play(*getCurrentAnimation());
  //animatedSprite.setLooped(true);

  //sf::Color color(100,100,255);
  //animatedSprite.setColor(color);

  switch(type)
  {
    case NPC::Goomba :

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
      animatedSprite.setColor(sf::Color::Red);
      //animatedSprite.setColor(sf::Color::White);
      //AddDirection(Orientation::SW, 50, getSpeed(), true);
      break;
  }

  // set up AnimatedSprite
  animatedSprite.setOrigin(16,16);
  animatedSprite.setPosition(position.x,position.y);

  // set hitbox for collision testing
  setHitbox(*animations.get(Animations::Hitbox).getSpriteSheet(), 20, 20);
  //hitbox.setPosition(position.x,position.y);


}

void NPC::collideWithEntity(const AnimatedEntity& a, sf::Time dt)
{
  if(!checkCollision(a))
    return;


  switch(a.getParentType())
  {
    case AnimatedEntity::HeroType :
      break;

    case AnimatedEntity::NPCType :
      break;

    case AnimatedEntity::WeaponType :
      if(a.getStatus() == AnimatedEntity::Attacking)
      {
        TakeDamage(a.getPower());
        std::cout<<getHP()<<std::endl;
      }
      break;

    case AnimatedEntity::ProjectileType :
      TakeDamage(a.getPower());
      std::cout<<getHP()<<std::endl;
      break;

    case AnimatedEntity::CollidableType :
      break;
  }

/*
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
    std::cout<<checkCollision(a)<<std::endl;
    std::cout<<getHP()<<std::endl;
  }
  else if(typeid(a) == typeid(Collidable))
  {
    // adjust position, possibly take damage
  }


*/
}

void NPC::playAnimation()
{

  switch(getStatus())
  {
    case AnimatedEntity::Idle :
      animatedSprite.play(idleAnimation); // or animatedSprite.stop() to revert back to first frame
      break;

    case AnimatedEntity::Moving :
      animatedSprite.play(moveAnimation);
      break;

    case AnimatedEntity::Attacked :
      animatedSprite.play(attackedAnimation);
      break;

    case AnimatedEntity::Grabbed :
      animatedSprite.play(grabbedAnimation);
      break;

    case AnimatedEntity::Thrown :
      animatedSprite.play(thrownAnimation);
      break;

    case AnimatedEntity::Die :
      animatedSprite.play(dieAnimation);
      animatedSprite.setLooped(false);
      break;

    case AnimatedEntity::Dead :
      animatedSprite.pause();
      //animatedSprite.play(deadAnimation);
      break;
  }
}
