
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

class NPC;
class Weapon;

class Hero : public AnimatedEntity
{
public:
                                Hero();

  void                          SetAnimations(const ResourceHolder<Animation, Animations::ID>& animations);

  std::shared_ptr<Animation>    grabAnimation;
  std::shared_ptr<Animation>    punchAnimation;
  std::shared_ptr<Animation>    kickAnimation;


  //virtual void                  restoreDefaultAnimation() { setCurrentAnimation(defaultAnimation); }

  void                          collideWithEntity(const AnimatedEntity& a, sf::Time dt);

  void                          PrimaryAttack();
  void                          SecondaryAttack();
  void                          Pickup(std::vector<std::shared_ptr<AnimatedEntity>>& vec_ptr_a);
  void                          Drop();
  void                          Throw();
  std::shared_ptr<Weapon>       getWeapon();
  std::shared_ptr<NPC>          grabbed_npc;     // used to hold grabbed NPCs
  void                          restoreDefaultState();


private:
                                Hero(const Hero&);              // Disallow copy constructor
                                Hero& operator=(const Hero&);   // Disallow assignment

  void                          PickupWeapon(std::vector< std::shared_ptr<Weapon> >& weap_vec);
  void                          DropWeapon();
  void                          ThrowWeapon();
  void                          PickupNPC(std::vector< std::shared_ptr<NPC> >& npc_vec);
  void                          DropNPC();
  void                          ThrowNPC();

  std::shared_ptr<Weapon>       weapon;
  std::shared_ptr<Weapon>       default_weapon;
};

#endif // HERO_H
