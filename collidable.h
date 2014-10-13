
#ifndef Collidable_H
#define Collidable_H

#include <SFML/Graphics.hpp>
#include "collidable.h"


class Collidable
{
  public:
    enum Type {
      SubwayDoor,         // NPC victory condition, no collision with Hero
      SubwayPlatform,     // NPCs will automatically collide if not attacked or thrown
      SubwayRail,         // collision results in death
      ImmovableObject,    // everything collides
    };

    Collidable(Type t, double x, double y, double width, double height);

    Type getType() { return type; }

    sf::Vector2f position;
    sf::Sprite sprite;

  private:
    Type type;

};

#endif

