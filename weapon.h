
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "animatedentity.h"
#include "direction.h"
#include "attack.h"

class Projectile;
class DataTable;

class Weapon : public AnimatedEntity
{
  public:
    enum Type {
      Hands,
      Pistol,
      Shotgun,
      Rifle,
      SMG,
      RocketLauncher,
      Dagger,
      ShortSword,
      Sword,
      LongSword,
      SingleAxe,
      DoubleAxe,
      Spear,
      TypeCount
    };
    // weapon that immbolizes NPC for period of time (ancient rope with balls on it)?

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
    unsigned          ammoCount;
    const Animation&  idleAnimation;
    const Animation&  moveAnimation;
    const Animation&  dieAnimation;
    const Animation&  primaryAttackAnimation;
    const Animation&  secondaryAttackAnimation;


};

#endif
