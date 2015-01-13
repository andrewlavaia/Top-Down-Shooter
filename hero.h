
#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "animatedentity.h"
#include "TextureManager.h"
#include "animation.h"
#include "animatedsprite.h"
#include "collidable.h"
#include "projectile.h"
#include "collision.h"
#include "attack.h"
#include "orientation.h"

class NPC;
class Weapon;

class Hero : public AnimatedEntity
{
public:

                                Hero();

  void                          CreateAnimations(const TextureManager& textures);

  double                        speed;
  double                        strength;

  Animation                     walkAnimation;
  Animation                     grabAnimation;
  Animation                     punchAnimation;
  Animation                     kickAnimation;

  virtual Animation*            getCurrentAnimation() { return currentAnimation; }
  virtual void                  setCurrentAnimation(Animation& a) { currentAnimation = &a; }
  virtual void                  restoreDefaultAnimation() { setCurrentAnimation(defaultAnimation); }

  void                          collideWithEntity(const AnimatedEntity& a);

  void                          PrimaryAttack(std::vector< std::shared_ptr<NPC> >& npc_vec);
  void                          SecondaryAttack(std::vector< std::shared_ptr<NPC> >& npc_vec);
  void                          Pickup(std::vector<std::shared_ptr<AnimatedEntity>>& vec_ptr_a);
  void                          Drop();
  void                          Throw();
  Weapon                        getWeapon();

  std::shared_ptr<NPC>          grabbed_npc;     // used to hold grabbed NPCs

  std::shared_ptr<Weapon>       weapon;
  std::unique_ptr<Weapon>       default_weapon;

private:
                                Hero(const Hero&);              // Disallow copy constructor
                                Hero& operator=(const Hero&);   // Disallow assignment

  void                          AttackNPC(Attack atk, double modifier, double rng, std::vector< std::shared_ptr<NPC> >& npc_vec);
  void                          PickupWeapon(std::vector< std::shared_ptr<Weapon> >& weap_vec);
  void                          DropWeapon();
  void                          ThrowWeapon();
  void                          PickupNPC(std::vector< std::shared_ptr<NPC> >& npc_vec);
  void                          DropNPC();
  void                          ThrowNPC();

  Animation*                    currentAnimation;


  double                        hp;

};

#endif // HERO_H
