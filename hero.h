
#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "animatedentity.h"
#include "resourceholder.h"
#include "animation.h"
#include "animatedsprite.h"
#include "collidable.h"
#include "projectile.h"
#include "collision.h"
#include "orientation.h"
#include "attack.h"

class NPC;
class Weapon;

class Hero : public AnimatedEntity
{
public:

  Hero(const ResourceHolder<Animation, Animations::ID>& animations);

  void                          collideWithEntity(const AnimatedEntity& a, sf::Time dt);
  void                          playAnimation();
  void                          MoveGrabbedEntities();
  void                          PrimaryAttack(std::vector<std::shared_ptr<AnimatedEntity>>& entities);
  void                          SecondaryAttack(std::vector<std::shared_ptr<AnimatedEntity>>& entities);
  void                          Pickup(std::vector<std::shared_ptr<AnimatedEntity>>& entities);
  void                          Drop();
  void                          Throw();
  std::shared_ptr<Weapon>       getWeapon();
  void                          restoreDefaultState();

private:
  Hero(const Hero&);              // Disallow copy constructor
  Hero& operator=(const Hero&);   // Disallow assignment

  void                          pAttack(Attack& attack, std::vector<std::shared_ptr<AnimatedEntity>>& entities);

  const ResourceHolder<Animation, Animations::ID>&  animations;
  std::shared_ptr<NPC>          grabbed_npc;
  std::shared_ptr<Weapon>       weapon;
  std::shared_ptr<Weapon>       default_weapon;

  const Animation&              idleAnimation;
  const Animation&              moveAnimation;
  const Animation&              dieAnimation;
  const Animation&              deadAnimation;
  const Animation&              grabAnimation;
  const Animation&              punchAnimation;
  const Animation&              kickAnimation;
};

#endif // HERO_H
