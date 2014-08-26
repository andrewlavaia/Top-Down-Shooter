
#include "weapon.h"

Weapon::Weapon(Type t)
{
  type = t;
  durability = 5;
  position.x = 50;
  position.y = 50;

  sf::Texture texture;
  texture.create(10,10);
  sprite.setTexture(texture); // aassign empty texture 20x20 pixels
  sprite.setColor(sf::Color(255,0,0,100)); // semi-transparent red hitbox
  sprite.setOrigin(5, 5);
  sprite.setPosition(position.x,position.y);

}

void Weapon::Attack()
{

}
