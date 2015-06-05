
#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/Graphics.hpp>
#include "animatedentity.h"

class DataTable;

class Collidable : public AnimatedEntity
{
  public:
    enum Type {
      Indestructible,       // replace with specific sub-types
      Destructible,         // replace with specific sub-types
      Exit,                 // exit to next room (can overlay other things on top, like doors etc)
      Boundary,             // invisible boundary for level
      TypeCount
    };

    explicit Collidable(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data, double x, double y, double width, double height);

    virtual void collideWithEntity(const AnimatedEntity& a, sf::Time dt);
    virtual void playAnimation();

    Type getType() const { return type; }

  private:
    Type type;
    const Animation& idleAnimation;

};

#endif

