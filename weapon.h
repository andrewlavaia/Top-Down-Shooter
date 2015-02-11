
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "animatedentity.h"
#include "direction.h"
#include "npc.h"
//#include "projectile.h"
#include "collidable.h"
#include "attack.h"

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
      SledgeHamemr,
      Pistol,
      Shotgun,
      Rifle,
      SMG,
      RocketLauncher,
      //Grenade
    };

    enum AttackType {
      Standard,
      Shoot,
    };

    Weapon(Type t, double x, double y);

    std::shared_ptr<Animation> primaryAttackAnimation;
    std::shared_ptr<Animation> secondaryAttackAnimation;

    std::unique_ptr<Attack> primaryAttack;
    std::unique_ptr<Attack> secondaryAttack;

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
