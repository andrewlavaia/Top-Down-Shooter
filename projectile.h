
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "animatedentity.h"

class Weapon;
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
                      const Weapon& weapon, double x = 0, double y = 0, double degrees = 0);

  virtual void collideWithEntity(const AnimatedEntity& a, sf::Time dt);
  virtual void playAnimation();

  Type getType() const { return type; }
  unsigned getRange() const { return range; }
  const Weapon& getOriginatingWeapon() const { return originatingWeapon; }

private:
  Type type;
  double rotation;
  const Animation& moveAnimation;
  const Animation& dieAnimation;
  unsigned range;
  const Weapon& originatingWeapon; // weapon that projectile originated from (needed for collision detection purposes)
};

#endif
