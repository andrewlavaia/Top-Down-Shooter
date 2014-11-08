
#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include "AnimatedEntity.h"
#include "TextureManager.h"
#include "animation.h"
#include "animatedsprite.h"
#include "direction.h"

class NPC : public AnimatedEntity
{
public:
  enum Type {
    Goomba,
    Chumba,
  };

  explicit                                NPC(Type type);

  void                                    CreateAnimations(const TextureManager& textures);  // required method to assign animations
  //Animation                               CreateAnimation(const sf::Texture& tex, unsigned width, unsigned height, unsigned sprite_count);
  //void                                    MoveAnimatedSprite(double interpolation);          // Animates sprite towards its new location based on time factor
  //void                                    MoveOppo(double d);

  //AnimatedSprite                          animatedSprite;
  Animation                               walkAnimation;
 // Animation*                              currentAnimation;

  //sf::Vector2f                            position;

  //std::vector<Direction>                  directions;
  //std::vector<Direction>::iterator        directions_it;
  //double                                  distance_travelled;

  double                                  getWeight() { return weight; }
  double                                  getSpeed()  { return speed;}


private:
  Type                                    type;
  double                                  speed;
  double                                  weight;

};


#endif // NPC_H
