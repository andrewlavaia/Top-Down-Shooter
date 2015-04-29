
#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include "animatedentity.h"
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
    TypeCount
  };

  explicit                                NPC(Type type, const ResourceHolder<Animation, Animations::ID>& animations);

  virtual void                            collideWithEntity(const AnimatedEntity& a, sf::Time dt);
  virtual void                            playAnimation();


private:
  Type                                    type;

  const Animation&                        idleAnimation;
  const Animation&                        moveAnimation;
  const Animation&                        dieAnimation;
  const Animation&                        deadAnimation;
  const Animation&                        attackedAnimation;
  const Animation&                        grabbedAnimation;
  const Animation&                        thrownAnimation;

};


#endif // NPC_H
