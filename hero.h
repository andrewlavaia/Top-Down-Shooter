
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

//Create an AnimationHolder class, that stores and retrieves Animations

class Hero : public AnimatedEntity
{
public:
                                Hero();

  void                          CreateAnimations(const ResourceHolder<sf::Texture, Textures::ID>& textures);
  double                        strength;

  std::shared_ptr<Animation>    walkAnimation;
  std::shared_ptr<Animation>    grabAnimation;
  std::shared_ptr<Animation>    punchAnimation;
  std::shared_ptr<Animation>    kickAnimation;


  //virtual void                  restoreDefaultAnimation() { setCurrentAnimation(defaultAnimation); }

  void                          collideWithEntity(const AnimatedEntity& a);

  void                          PrimaryAttack();
  //void                          SecondaryAttack(std::vector< std::shared_ptr<NPC> >& npc_vec);
  void                          Pickup(std::vector<std::shared_ptr<AnimatedEntity>>& vec_ptr_a);
  void                          Drop();
  void                          Throw();
  std::shared_ptr<Weapon>       getWeapon();

  std::shared_ptr<NPC>          grabbed_npc;     // used to hold grabbed NPCs

  std::shared_ptr<Weapon>       weapon;
  std::shared_ptr<Weapon>       default_weapon;

private:
                                Hero(const Hero&);              // Disallow copy constructor
                                Hero& operator=(const Hero&);   // Disallow assignment

  //void                          AttackNPC(Attack atk, double modifier, double rng, std::vector< std::shared_ptr<NPC> >& npc_vec);
  void                          PickupWeapon(std::vector< std::shared_ptr<Weapon> >& weap_vec);
  void                          DropWeapon();
  void                          ThrowWeapon();
  void                          PickupNPC(std::vector< std::shared_ptr<NPC> >& npc_vec);
  void                          DropNPC();
  void                          ThrowNPC();

};

#endif // HERO_H
