
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
  };

  explicit                                NPC(Type type, ResourceHolder<Animation, Animations::ID>& animations);

  std::shared_ptr<Animation>              attackedAnimation;
  std::shared_ptr<Animation>              grabbedAnimation;
  std::shared_ptr<Animation>              thrownAnimation;

  virtual void                            collideWithEntity(const AnimatedEntity& a, sf::Time dt);


private:
  Type                                    type;

};


#endif // NPC_H
