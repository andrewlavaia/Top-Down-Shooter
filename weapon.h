
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "animatedentity.h"
#include "direction.h"
#include "npc.h"
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

    Weapon(Type t, double x, double y, const ResourceHolder<Animation, Animations::ID>& animations);

    std::shared_ptr<Animation> primaryAttackAnimation;
    std::shared_ptr<Animation> secondaryAttackAnimation;

    std::unique_ptr<Attack> primaryAttack;
    std::unique_ptr<Attack> secondaryAttack;
    std::unique_ptr<Projectile> ammoType;

    Type        getType()                 { return type; }
    int         getRange()                { return range; }
    //int       getDurability()          { return durability; }
    //void      reduceDurability()       { durability--; }

    virtual void collideWithEntity(const AnimatedEntity& a, sf::Time dt);

  private:
    Type type;
    int range;



    //int durability; // can use weapons hitpoints instead




};

#endif
