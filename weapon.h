
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include  "direction.h"
#include "attack.h"
#include "animatedentity.h"

#include "npc.h"
#include "projectile.h"
#include "collidable.h"

class Hero;

// Level creates the unique_ptr to all new weapons
// Hero creates the Hands weapon any time another weapon is not held

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

    Weapon(Type t);

    Type      getType()                { return type; }
    Attack    getPrimaryAttack()       { return attack1; }
    Attack    getSecondaryAttack()     { return attack2; }
    double    getAttackModifier()      { return attack_modifier; }
    double    getRange()               { return range; }
    int       getDurability()          { return durability; }
    void      reduceDurability()       { durability--; }

    //Animation throwAnimation;

    virtual Animation* getCurrentAnimation() { return currentAnimation; }
    virtual void setCurrentAnimation(Animation& a) { currentAnimation = &a; }
    virtual void restoreDefaultAnimation() { setCurrentAnimation(defaultAnimation); }
    virtual void collideWithEntity(const AnimatedEntity& a);


  private:
    Type type;
    Animation* currentAnimation;
    Attack attack1;
    Attack attack2;
    int durability;
    double attack_modifier;
    double range;
};

#endif
