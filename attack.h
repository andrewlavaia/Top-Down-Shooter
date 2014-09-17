
#ifndef ATTACK_H
#define ATTACK_H

#include <SFML/Graphics.hpp>
#include "animation.h"


class Attack
{
  public:
    enum Type {
      Grab,
      Push,
      Smash,
    };

    Attack(Type t) { type = t; }

    Type getType() { return type; }
    void setType(Attack::Type t) { type = t; }
    Animation getAnimation() { return animation; };


  private:
    Type type;
    Animation animation;

};

#endif
