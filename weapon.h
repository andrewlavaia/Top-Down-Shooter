
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "animatedentity.h"
#include "direction.h"
#include "npc.h"
//#include "projectile.h"
#include "collidable.h"

class Hero;
class Projectile;

class Weapon : public AnimatedEntity
{
  public:
    enum Type {
      Hands,
      Pole,
      Lasso,
      Pistol,
      RocketLauncher,

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

    enum AttackType {
      Standard,
      Shoot
    };

    Weapon(Type t, double x, double y);

    std::shared_ptr<Animation> primaryAttackAnimation;
    std::shared_ptr<Animation> secondaryAttackAnimation;

    Type        getType()                 { return type; }
    AttackType  getPrimaryAttackType()    { return primaryAttackType; }
    AttackType  getSecondaryAttackType()  { return secondaryAttackType; }
    int         getRange()                { return range; }
    std::unique_ptr<Projectile> ammoType;
    //int       getDurability()          { return durability; }
    //void      reduceDurability()       { durability--; }

    virtual void collideWithEntity(const AnimatedEntity& a, sf::Time dt);

  private:
    Type type;
    AttackType primaryAttackType;
    AttackType secondaryAttackType;
    int range;



    //int durability; // can use weapons hitpoints instead




};

#endif
