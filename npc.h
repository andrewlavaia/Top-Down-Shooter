
#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "animatedentity.h"
#include "animation.h"
#include "animatedsprite.h"
#include "direction.h"

class Weapon;
class Attack;
class Level;
class DataTable;


class NPC : public AnimatedEntity
{
public:
  enum Type {
    Sheep,
    McGinger,
    BigRick,
    UglyAmy,
    TooCoolJack,
    DeNiro,
    Barnaby,
    ToughSugar,
    AmbiguousAlex,
    BaldingSam,
    TypeCount
  };

  enum Temprament { // used to determine whether npc will charge and attack hero when close enough
    Aggressive,
    Passive,
  };

  NPC(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data, double x, double y, std::shared_ptr<Weapon> weap);

  virtual void                            collideWithEntity(const AnimatedEntity& a, sf::Time dt);
  virtual void                            playAnimation();
  virtual void                            Move();
  virtual void                            ifDead();

  void                                    engageHero(const AnimatedEntity& hero, Level& level);
  Temprament                              getTemprament() const { return temprament; }
  std::shared_ptr<Weapon>                 getWeapon() const;
  void                                    dropWeapon();

private:
  Type                                    type;
  Temprament                              temprament;
  std::shared_ptr<Weapon>                 weapon;
  std::shared_ptr<Weapon>                 default_weapon;
  const Animation&                        idleAnimation;
  const Animation&                        moveAnimation;
  const Animation&                        dieAnimation;
  const Animation&                        deadAnimation;
  const Animation&                        attackedAnimation;
  const Animation&                        grabbedAnimation;
  const Animation&                        thrownAnimation;

  void                                    pAttack(Attack& attack, Level& level);
};

#endif // NPC_H
