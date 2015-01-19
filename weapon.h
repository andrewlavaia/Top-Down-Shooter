
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "animatedentity.h"
#include "direction.h"
#include "npc.h"
#include "projectile.h"
#include "collidable.h"

class Hero;

class Weapon : public AnimatedEntity
{
  public:
    enum Type {
      Hands,
      Pole,
      Lasso,

      /*
      Hands,
      Sword,
      SledgeHammer,
      Axe,
      Pitchfork,
      Knife,
      Pistol(s),
      Shotgun(s),
      Rifle(s),
      SMG(s),
      RocketLauncher,
      Grenade(s)

      */
    };

    Weapon(Type t, double x, double y);

    std::shared_ptr<Animation> primaryAttackAnimation;
    std::shared_ptr<Animation> secondaryAttackAnimation;

    Type      getType()                { return type; }
    double    getDamageModifier()      { return damage_modifier; }
    double    getRange()               { return range; }
    int       getDurability()          { return durability; }
    void      reduceDurability()       { durability--; }

    virtual void collideWithEntity(const AnimatedEntity& a);

  private:
    Type type;
    int durability;
    double damage_modifier;
    double range;


};

#endif
