
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include  "direction.h"
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

    Type      getType()                { return type; }
    Attack    getPrimaryAttack()       { return attack1; }
    Attack    getSecondaryAttack()     { return attack2; }
    double    getAttackModifier()      { return attack_modifier; }
    double    getRange()               { return range; }
    int       getDurability()          { return durability; }
    void      reduceDurability()       { durability--; }

    void      MoveSprite(double interpolation);

    // used for automated movement of weapons when thrown
    std::vector<Direction>                  directions;
    std::vector<Direction>::iterator        directions_it;
    double                                  distance_travelled;

    sf::Sprite sprite;
    sf::Vector2f position;

  private:
    Type type;
    Attack attack1;
    Attack attack2;
    int durability;
    double attack_modifier;
    double range;
};

#endif
