
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "animatedentity.h"
#include "orientation.h"

#include "hero.h"
#include "npc.h"
#include "weapon.h"
#include "collidable.h"

class Projectile : public AnimatedEntity
{
public:

  enum Type{
    Bullet,
    Rocket,
    Arrow,
    Grenade,
    Knife,
  };

  Projectile(Type t, double x, double y, Orientation::Type o);

  Type getType() { return type; }
  double getSpeed() { return speed; }
  double getRange() { return range; }
  double getDamage() { return damage; }

  //virtual void restoreDefaultAnimation() { setCurrentAnimation(defaultAnimation); }
  //virtual Animation* getCurrentAnimation() { return currentAnimation; }
  //virtual void setCurrentAnimation(Animation& a) { currentAnimation = &a; }
  virtual void collideWithEntity(const AnimatedEntity& a);

private:
  Type type;
  Orientation::Type orientation;

  double speed;
  double range;
  double damage;
};

#endif
