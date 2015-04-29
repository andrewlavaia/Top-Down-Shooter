
#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/Graphics.hpp>
#include "animatedentity.h"
#include "collidable.h"


#include "hero.h"
#include "npc.h"
#include "weapon.h"
#include "projectile.h"

class Collidable : public AnimatedEntity
{
  public:
    enum Type {
      Exit,                 // exit to next room (can overlay other things on top, like doors etc)
      Indestructible,       // replace with specific sub-types
      Destructible,         // replace with specific sub-types
      TypeCount
    };

    Collidable(Type t, double x, double y, double width, double height, const ResourceHolder<Animation, Animations::ID>& animations);

    virtual void collideWithEntity(const AnimatedEntity& a, sf::Time dt);
    virtual void playAnimation();

    Type getType() const { return type; }

  private:
    Type type;
    const Animation& idleAnimation;

};

#endif

