
#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "TextureManager.h"
#include "animation.h"
#include "animatedsprite.h"
#include "npc.h"
#include "weapon.h"
#include "collision.h"
#include "attack.h"
#include "orientation.h"

class Hero
{
public:

                                Hero();

  void                          CreateAnimations(const TextureManager& textures);
  void                          MoveAnimatedSprite(double interpolation);


  sf::Vector2f                  position;
  AnimatedSprite                animatedSprite;

  double                        speed;
  double                        strength;

  Animation                     walkAnimationDown;
  Animation                     walkAnimationUp;
  Animation                     walkAnimationRight;
  Animation                     walkAnimationLeft;
  Animation*                    currentAnimation;


  void                          PrimaryAttack(std::vector< std::unique_ptr<NPC> >& npc_vec);
  void                          SecondaryAttack(std::vector< std::unique_ptr<NPC> >& npc_vec);
  void                          Throw(std::vector< std::unique_ptr<NPC> >& npc_vec,
                                      std::vector< std::unique_ptr<Weapon> >& weap_vec);
  void                          Pickup(std::vector< std::unique_ptr<NPC> >& npc_vec,
                                      std::vector< std::unique_ptr<Weapon> >& weap_vec);
  void                          Drop(std::vector< std::unique_ptr<NPC> >& npc_vec,
                                      std::vector< std::unique_ptr<Weapon> >& weap_vec);

  std::unique_ptr<Weapon>       weapon;
  std::unique_ptr<NPC>          grabbed_npc;     // used to hold grabbed NPCs
  std::unique_ptr<NPC>          roped_npc;       // used to hold roped NPCs

  // getters + setters
  void                          setOrientation(Orientation::Type t) { orientation.setType(t); }
  Orientation                   getOrientationObj() {return orientation; }
  Orientation::Type             getOrientation() { return orientation.getType(); }



private:
                                Hero(const Hero&);              // Disallow copy constructor
                                Hero& operator=(const Hero&);   // Disallow assignment

  void                          AttackNPC(Attack atk, double modifier, double rng, std::vector< std::unique_ptr<NPC> >& npc_vec);
  void                          ThrowNPC(std::vector< std::unique_ptr<NPC> >& npc_vec);
  void                          ThrowWeapon(std::vector< std::unique_ptr<Weapon> >& weap_vec);
  void                          PickupWeapon(std::vector< std::unique_ptr<Weapon> >& weap_vec);
  void                          DropWeapon(std::vector< std::unique_ptr<Weapon> >& weap_vec);
  void                          PickupNPC(std::vector< std::unique_ptr<NPC> >& npc_vec);
  void                          DropNPC(std::vector< std::unique_ptr<NPC> >& npc_vec);

  std::unique_ptr<Weapon>       m_weapon_storage;  // used to hold Hands weapon permanently
  Orientation                   orientation;




};

#endif // HERO_H
