
#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "animatedentity.h"
#include "resourceholder.h"
#include "animation.h"
#include "animatedsprite.h"
#include "collision.h"
#include "orientation.h"
#include "attack.h"

class Weapon;
class NPC;
class DataTable;

class Hero : public AnimatedEntity
{
public:

  enum Type {
    Bob,
    SuitDrew,
    GeezerHarry,
    DirtyPete,
    TypeCount
  };

  Hero(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data);

  void                          collideWithEntity(const AnimatedEntity& a, sf::Time dt);
  void                          playAnimation();
  void                          MoveGrabbedEntities();
  void                          PrimaryAttack(std::vector<std::shared_ptr<AnimatedEntity>>& entities);
  void                          SecondaryAttack(std::vector<std::shared_ptr<AnimatedEntity>>& entities);
  void                          Pickup(std::vector<std::shared_ptr<AnimatedEntity>>& entities);
  void                          Drop();
  void                          Throw();
  std::shared_ptr<Weapon>       getWeapon();

private:
  Hero(const Hero&);              // Disallow copy constructor
  Hero& operator=(const Hero&);   // Disallow assignment

  void                          pAttack(Attack& attack, std::vector<std::shared_ptr<AnimatedEntity>>& entities);

  Type                          type;
  const ResourceHolder<Animation, Animations::ID>&  animations;
  const DataTable&              data;
  std::shared_ptr<NPC>          grabbed_npc;
  std::shared_ptr<Weapon>       weapon;
  std::shared_ptr<Weapon>       default_weapon;

  const Animation&              idleAnimation;
  const Animation&              moveAnimation;
  const Animation&              dieAnimation;
  const Animation&              deadAnimation;
  const Animation&              attackedAnimation;
  const Animation&              grabAnimation;

};

#endif // HERO_H
