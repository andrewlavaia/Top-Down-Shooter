
#include "npc.h"
#include "datatables.h"

NPC::NPC(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data, double x, double y)
  : AnimatedEntity(AnimatedEntity::NPCType),
    type(t),
    idleAnimation(animations.get(data.NPCTable[t].idleAnimationID)),
    moveAnimation(animations.get(data.NPCTable[t].moveAnimationID)),
    dieAnimation(animations.get(data.NPCTable[t].dieAnimationID)),
    deadAnimation(animations.get(data.NPCTable[t].deadAnimationID)),
    attackedAnimation(animations.get(data.NPCTable[t].attackedAnimationID)),
    grabbedAnimation(animations.get(data.NPCTable[t].grabbedAnimationID)),
    thrownAnimation(animations.get(data.NPCTable[t].thrownAnimationID))
{
  setHitPoints(data.NPCTable[t].hitpoints);
  setSpeed(data.NPCTable[t].speed);
  setPower(data.NPCTable[t].power);

  position.x = x;
  position.y = y;

  animatedSprite.setPosition(position.x, position.y);
  animatedSprite.setOrigin(15,15);
  setHitbox(*animations.get(Animations::Hitbox).getSpriteSheet(),
          data.NPCTable[t].hitboxDimensions.x,
          data.NPCTable[t].hitboxDimensions.y);

  setStatus(AnimatedEntity::Moving);
  animatedSprite.play(moveAnimation);
  animatedSprite.setLooped(false);
  animatedSprite.setFrameTime(sf::seconds(0.10));
  animatedSprite.setColor(data.NPCTable[t].color);
  animatedSprite.setScale(1,1);

  // set AI
  switch(type)
  {
    case NPC::Goomba :
      AddDirection(Orientation::S, 100, getSpeed(), false);
      //AddDirection(Orientation::NW, 100, getSpeed(), true);
      //AddDirection(Orientation::NE, 50, getSpeed(), true);
      //AddDirection(Orientation::SW, 50, getSpeed(), true);

      break;

    case NPC::Chumba :
      AddDirection(Orientation::S,  100, getSpeed(), true);
      AddDirection(Orientation::E,  100, getSpeed(), true);
      AddDirection(Orientation::NW, 100, getSpeed(), true);
      //AddDirection(Orientation::SW, 50, getSpeed(), true);

      break;
  }

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
      if(a.getStatus() == AnimatedEntity::AttackingPrimary || a.getStatus() == AnimatedEntity::AttackingSecondary)
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
      animatedSprite.play(deadAnimation);
      animatedSprite.setLooped(true);
      break;

    default :
      animatedSprite.pause();
      break;
  }
}
