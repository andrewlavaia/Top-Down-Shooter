
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

  void CreateSprite(const TextureManager& textures);
  void CreateAnimatedSprite();
  void CreateAnimations(const TextureManager& textures);

  void MoveSprite(double interpolation);   // Animates sprite towards its new location based on time factor

  sf::Vector2f position;

  sf::Sprite sprite;
  AnimatedSprite animatedSprite;

  double speed;
  double strength;

  Animation walkAnimationDown;
  Animation walkAnimationUp;
  Animation walkAnimationRight;
  Animation walkAnimationLeft;

  Animation* currentAnimation;


private:


};



#endif // HERO_H
