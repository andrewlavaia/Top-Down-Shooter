
#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "TextureManager.h"
#include "animation.h"
#include "animatedsprite.h"
#include "weapon.h"

class Hero
{
public:
                                Hero();

  void                          CreateAnimatedSprite();
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

  void                          PickupWeapon(std::vector< std::unique_ptr<Weapon> >& v);
  void                          DropWeapon(std::vector< std::unique_ptr<Weapon> >& v);

  std::unique_ptr<Weapon>       weapon;

private:
                                Hero(const Hero&);              // Disallow copy constructor
                                Hero& operator=(const Hero&);   // Disallow assignment



};

#endif // HERO_H
