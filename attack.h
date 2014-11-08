
#ifndef ATTACK_H
#define ATTACK_H

#include <SFML/Graphics.hpp>
#include "animation.h"


class Attack
{
  public:
    enum Type {
      Push,
      Kick,
      Smash, // a powerful push
      RopeEm,
    };

    Attack(Type t) { type = t; }

    Type getType() { return type; }
    Animation getAnimation() { return animation; }

    void setType(Attack::Type t) { type = t; }
    void setAnimation(Animation a) { animation = a; }

  private:
    Type type;
    Animation animation;

};

#endif

