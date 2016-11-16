
#ifndef ATTACK_H
#define ATTACK_H

#include <SFML/Graphics.hpp>
#include "animation.h"

class Attack
{
public:

  enum Type {
    Standard,
    Shoot,
    Thrust,
  };

  Attack(Type t, double attack_speed = 0.5)
  {
    type = t;
    attackSpeed = attack_speed;
    cooldown = sf::Time::Zero;
  }

  bool canAttack() { return cooldown < sf::Time::Zero; }
  void reduceCooldown(sf::Time dt) { cooldown -= dt; }
  void resetCooldown() { cooldown = sf::seconds(attackSpeed); }

  Type getType() const { return type; }
  double getAttackSpeed() const { return attackSpeed; }


private:
  Type type;
  double attackSpeed;
  sf::Time cooldown;

};



#endif
