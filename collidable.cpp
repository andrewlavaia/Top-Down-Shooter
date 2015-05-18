

#include "collidable.h"
#include "datatables.h"

Collidable::Collidable(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data, double x, double y, double width, double height)
  : AnimatedEntity(AnimatedEntity::CollidableType),
    type(t),
    idleAnimation(animations.get(data.CollidableTable[t].idleAnimationID))
{
  setHitPoints(data.CollidableTable[t].hitpoints);
  setSpeed(data.CollidableTable[t].speed);
  setPower(data.CollidableTable[t].power);

  position.x = x + width/2;
  position.y = y + height/2;

  animatedSprite.setPosition(position.x + width/2, position.y + height/2);
  animatedSprite.setOrigin(width/2, height/2);
  setHitbox(*animations.get(Animations::Hitbox).getSpriteSheet(), width, height);

  setStatus(AnimatedEntity::Idle);
  animatedSprite.play(idleAnimation); // sets initial animation
  animatedSprite.setLooped(true);
  animatedSprite.setFrameTime(sf::seconds(0.16));
  animatedSprite.setColor(data.CollidableTable[t].color);

  animatedSprite.setScale(width/idleAnimation.getSpriteSheet()->getSize().x,
                          height/idleAnimation.getSpriteSheet()->getSize().y);

}

void Collidable::collideWithEntity(const AnimatedEntity& a, sf::Time dt)
{
  if (!checkCollision(a))
    return;

  switch(a.getParentType())
  {
    case AnimatedEntity::HeroType :
      break;

    case AnimatedEntity::NPCType :
      break;

    case AnimatedEntity::WeaponType :
      TakeDamage(a.getPower());
      break;

    case AnimatedEntity::ProjectileType :
      TakeDamage(a.getPower());
      break;

    case AnimatedEntity::CollidableType :
      break;
  }
}

void Collidable::playAnimation()
{
  switch(getStatus())
  {
    case AnimatedEntity::Idle :
      animatedSprite.play(idleAnimation);
      break;

    default :
      animatedSprite.pause();
      break;
  }
}
