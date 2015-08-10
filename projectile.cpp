
#include "projectile.h"
#include "datatables.h"

Projectile::Projectile(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data,
                       const Weapon& weapon, double x, double y, double degrees)
  : AnimatedEntity(AnimatedEntity::ProjectileType),
    type(t),
    rotation(degrees),
    moveAnimation(animations.get(data.ProjectileTable[t].moveAnimationID)),
    dieAnimation(animations.get(data.ProjectileTable[t].dieAnimationID)),
    range(data.ProjectileTable[t].range),
    originatingWeapon(weapon)
{
  setHitPoints(data.ProjectileTable[t].hitpoints);
  setMaxHitPoints(data.ProjectileTable[t].hitpoints);
  setSpeed(data.ProjectileTable[t].speed);
  setPower(data.ProjectileTable[t].power);

  position.x = x;
  position.y = y;

  animatedSprite.setPosition(position.x, position.y);
  setHitbox(*animations.get(Animations::Hitbox).getSpriteSheet(),
            data.ProjectileTable[t].hitboxDimensions.x,
            data.ProjectileTable[t].hitboxDimensions.y);

  // Projectile is always moving when created
  setStatus(AnimatedEntity::Moving);
  AddDirection(getOrientation().getType(), range, getSpeed(), false, rotation);

  animatedSprite.play(moveAnimation);
  animatedSprite.setLooped(true);
  //animatedSprite.setFrameTime(sf::seconds(0.16));
  animatedSprite.setColor(data.ProjectileTable[t].color);

  setScaleFactor(data.ProjectileTable[t].scaleFactor);
  animatedSprite.setScale( getScaleFactor(), getScaleFactor() );
}

void Projectile::collideWithEntity(const AnimatedEntity& a, sf::Time dt)
{
  if(!checkCollision(a))
    return;

  switch(a.getParentType())
  {
    case AnimatedEntity::HeroType :
      Destroy();
      break;

    case AnimatedEntity::NPCType :
      // first check to see if the projectiles came from the weapon that the NPC is holding
      if( &(getOriginatingWeapon()) != &(*dynamic_cast<const NPC&>(a).getWeapon()) )
      {
        Destroy();
      }
      break;

    case AnimatedEntity::WeaponType :
      break;

    case AnimatedEntity::ProjectileType :
      break;

    case AnimatedEntity::CollidableType :
      Destroy();
      break;
  }
}

void Projectile::playAnimation()
{
  switch(getStatus())
  {
    case AnimatedEntity::Idle :
      animatedSprite.pause();
      break;

    case AnimatedEntity::Moving :
      animatedSprite.play(moveAnimation);
      break;

    case AnimatedEntity::Die :
      animatedSprite.play(dieAnimation);
      break;

    case AnimatedEntity::Dead :
      animatedSprite.pause();
      break;

    default :
      animatedSprite.pause();
      break;
  }
}
