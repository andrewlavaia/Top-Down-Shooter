
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>

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

    void Attack();

    Type getType() { return type; }
    int getDurability() { return durability; }
    void reduceDurability() { durability--; }

    sf::Sprite sprite;
    sf::Vector2f position;

  private:
    Type type;
    int durability;
};

#endif
