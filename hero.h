
#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "TextureManager.h"
#include "animation.h"
#include "animatedsprite.h"

class Hero
{
public:
  Hero();

  void CreateAnimatedSprite();                            // psuedo constructor for AnimatedSprite
  void CreateAnimations(const TextureManager& textures);  // required method to assign animations
  void MoveAnimatedSprite(double interpolation);          // Animates sprite towards its new location based on time factor

  sf::Vector2f position;

  AnimatedSprite animatedSprite;

  double speed;
  double strength;

  Animation walkAnimationDown;
  Animation walkAnimationUp;
  Animation walkAnimationRight;
  Animation walkAnimationLeft;

  Animation* currentAnimation;

private:
  Hero(const Hero&);              // Disallow copy constructor
  Hero& operator=(const Hero&);   // Disallow assignment

};

#endif // HERO_H
