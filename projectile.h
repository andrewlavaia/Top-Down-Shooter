
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "animatedentity.h"
#include "orientation.h"

#include "hero.h"
#include "npc.h"
#include "collidable.h"
#include "weapon.h"

class Projectile : public AnimatedEntity
{
public:

  enum Type{
    Empty,
    Bullet,
    BuckShot,
    Rocket,
    //Arrow,
    //Grenade,
    TypeCount
  };

  Projectile(Type t, const ResourceHolder<Animation, Animations::ID>& animations, double x = 0, double y = 0, Orientation::Type o = Orientation::N);

  Type getType() { return type; }
  double getRange() { return range; }

  virtual void collideWithEntity(const AnimatedEntity& a, sf::Time dt);
  virtual void playAnimation();

private:
  Type type;
  Orientation::Type orientation;

  const Animation& moveAnimation;
  const Animation& dieAnimation;

  int range;
};

#endif
