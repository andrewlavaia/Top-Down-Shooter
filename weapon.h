
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "attack.h"

// Level creates the unique_ptr to all new weapons
// Hero creates the Hands weapon any time another weapon is not held

class Weapon
{
  public:
    enum Type {
      Hands,
      Pole,
      Lasso,
      GarbageCan
    };

    Weapon(Type t);

    Type getType() { return type; }
    Attack getPrimaryAttack() { return attack1; }
    Attack getSecondaryAttack() {return attack2; }
    int getDurability() { return durability; }
    void reduceDurability() { durability--; }

    sf::Sprite sprite;
    sf::Vector2f position;

  private:
    Type type;
    Attack attack1;
    Attack attack2;
    int durability;
    int attack_modifier;
};

#endif
