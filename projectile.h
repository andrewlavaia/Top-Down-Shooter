
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "animatedentity.h"

class DataTable;

class Projectile : public AnimatedEntity
{
public:

  enum Type{
    Empty,
    Bullet,
    BuckShot,
    Rocket,
    TypeCount
  };

  explicit Projectile(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data,
                      double x = 0, double y = 0, double degrees = 0);

  virtual void collideWithEntity(const AnimatedEntity& a, sf::Time dt);
  virtual void playAnimation();

  Type getType() const { return type; }
  unsigned getRange() const { return range; }

private:
  Type type;
  double rotation;
  const Animation& moveAnimation;
  const Animation& dieAnimation;
  unsigned range;
  //const Weapon& firedWeapon; // weapon that projectile originated from (needed for collision detection purposes)
};

#endif
