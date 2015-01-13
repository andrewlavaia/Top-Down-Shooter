
#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include "AnimatedEntity.h"
#include "TextureManager.h"
#include "animation.h"
#include "animatedsprite.h"
#include "direction.h"

#include "hero.h"
#include "weapon.h"
#include "projectile.h"
#include "collidable.h"

class NPC : public AnimatedEntity
{
public:
  enum Type {
    Goomba,
    Chumba,

    /*
    Zombie,
    Human,
    */
  };

  explicit                                NPC(Type type, TextureManager& texture);

  Animation                               defaultAnimation;
  Animation                               attackedAnimation;
  Animation                               grabbedAnimation;
  Animation                               thrownAnimation;

  virtual Animation* getCurrentAnimation() { return currentAnimation; }
  virtual void setCurrentAnimation(Animation& a) { currentAnimation = &a; }
  virtual void restoreDefaultAnimation() { setCurrentAnimation(defaultAnimation); }
  virtual void                            collideWithEntity(const AnimatedEntity& a);

  double                                  getWeight() { return weight; }
  double                                  getSpeed()  { return speed;}


private:
  Type                                    type;
  Animation*                              currentAnimation;
  double                                  speed;
  double                                  weight;
  double                                  hp;

};


#endif // NPC_H
