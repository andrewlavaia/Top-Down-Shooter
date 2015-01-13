
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
      SubwayDoor,         // NPC victory condition, no collision with Hero
      SubwayPlatform,     // NPCs will automatically collide if not attacked or thrown
      SubwayRail,         // collision results in death
      ImmovableObject,    // everything collides

      /*
      Exit                 // exit to next room
      BreakableObject      // windows, fences, containers, etc
      IndestructibleObject // steel walls, trees, etc
      Projectile           // bullets
      Fire
      */
    };

    Collidable(Type t, int x, int y, int width, int height);


    virtual Animation* getCurrentAnimation() { return currentAnimation; }
    virtual void setCurrentAnimation(Animation& a) { currentAnimation = &a; }
    virtual void restoreDefaultAnimation() { setCurrentAnimation(defaultAnimation); }
    virtual void collideWithEntity(const AnimatedEntity& a);

    Type getType() { return type; }

    //sf::Vector2f position;
    //sf::Sprite sprite;

  private:
    Type type;
    Animation* currentAnimation;

};

#endif

