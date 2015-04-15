
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

  std::shared_ptr<Animation>    moveAnimation;
  std::shared_ptr<Animation>    destroyAnimation;
  std::shared_ptr<Animation>    grabAnimation;
  std::shared_ptr<Animation>    punchAnimation;
  std::shared_ptr<Animation>    kickAnimation;

  void                          collideWithEntity(const AnimatedEntity& a, sf::Time dt);
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
};

#endif // HERO_H
