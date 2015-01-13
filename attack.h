
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
      /*
      Punch,        // default primary
      Kick,         // default secondary
      Bite,
      MeleeBash1H   // (hammer, pistol whip, etc)
      MeleeBash2H,  // (sledgehammer, rifle butt, etc)
      MeleePoke,    // (pitch fork)
      MeleeSlash,   // (swords, knives, etc)
      PistolShot,
      ShotgunShot,
      RifleShot,
      SMGShot,
      BowShot,
      Explosive,    // (rocket launcher, grenade, etc)
      Stun,         // (taser, etc)
      */
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

