
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "animatedentity.h"
#include "orientation.h"

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

  explicit Projectile(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data, double x = 0, double y = 0, Orientation::Type o = Orientation::N);

  virtual void collideWithEntity(const AnimatedEntity& a, sf::Time dt);
  virtual void playAnimation();

  Type getType() const { return type; }
  unsigned getRange() const { return range; }

private:
  Type type;
  Orientation::Type orientation;
  const Animation& moveAnimation;
  const Animation& dieAnimation;
  unsigned range;
};

#endif
