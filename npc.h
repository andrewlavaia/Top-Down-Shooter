
#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "animation.h"
#include "animatedsprite.h"
#include "direction.h"

class NPC
{
public:
  enum Type {
    Goomba,
    Chumba,
  };

  explicit                                NPC(Type type);

  void                                    CreateAnimatedSprite();                            // psuedo constructor for AnimatedSprite
  void                                    CreateAnimations(const TextureManager& textures);  // required method to assign animations
  void                                    MoveAnimatedSprite(double interpolation);          // Animates sprite towards its new location based on time factor

  AnimatedSprite                          animatedSprite;
  Animation                               walkAnimationDown;
  Animation                               walkAnimationUp;
  Animation                               walkAnimationRight;
  Animation                               walkAnimationLeft;
  Animation*                              currentAnimation;

  sf::Vector2f                            position;
  double                                  speed;
  double                                  weight;
  std::vector<Direction>                  directions;
  std::vector<Direction>::const_iterator  directions_it;
  double                                  distance_travelled;

private:
  Type                                     type;

};


#endif // NPC_H
