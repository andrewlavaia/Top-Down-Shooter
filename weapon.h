
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "animatedentity.h"
#include "direction.h"
#include "npc.h"
#include "collidable.h"
#include "attack.h"
#include "datatables.h"

class Hero;
class Projectile;

class Weapon : public AnimatedEntity
{
  public:
    enum Type {
      Hands,
      Pole,
      Sword,
      Axe,
      Pistol,
      Shotgun,
      Rifle,
      SMG,
      RocketLauncher,
      TypeCount
    };

    explicit Weapon(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data, double x, double y);

    virtual void collideWithEntity(const AnimatedEntity& a, sf::Time dt);
    virtual void playAnimation();

    Type getType() const { return type; }
    unsigned getRange() const { return range; }

    std::unique_ptr<Attack> primaryAttack;
    std::unique_ptr<Attack> secondaryAttack;
    std::unique_ptr<Projectile> ammoType;

  private:
    Type              type;
    unsigned          range;
    const Animation&  idleAnimation;
    const Animation&  moveAnimation;
    const Animation&  dieAnimation;
    const Animation&  primaryAttackAnimation;
    const Animation&  secondaryAttackAnimation;
    unsigned          ammoCount;

};

#endif
