
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

  void                          PickupWeapon(std::vector< std::unique_ptr<Weapon> >& weap_vec);
  void                          DropWeapon(std::vector< std::unique_ptr<Weapon> >& weap_vec);
  void                          PrimaryAttack(std::vector< std::unique_ptr<NPC> >& npc_vec);
  void                          SecondaryAttack(std::vector< std::unique_ptr<NPC> >& npc_vec);
  void                          ThrowNPC(std::vector< std::unique_ptr<NPC> >& npc_vec);

  std::unique_ptr<Weapon>       weapon;
  std::unique_ptr<NPC>          grabbed_npc;     // used to hold grabbed NPCs

  // helpers
  void                          setOrientation(Orientation::Type t) { orientation.setType(t); }
  Orientation::Type             getOrientation() { return orientation.getType(); }



private:
                                Hero(const Hero&);              // Disallow copy constructor
                                Hero& operator=(const Hero&);   // Disallow assignment

  void                          AttackNPC(Attack atk, std::vector< std::unique_ptr<NPC> >& npc_vec);

  std::unique_ptr<Weapon>       m_weapon_storage;  // used to hold Hands weapon permanently
  Orientation                   orientation;




};

#endif // HERO_H
