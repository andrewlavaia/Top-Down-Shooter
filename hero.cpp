#include "hero.h"

Hero::Hero()
{
  x = 50;
  y = 50;

  if (!texture.loadFromFile("character-sprite-map.gif"))
  {
      // error...
  }
  texture.setSmooth(true);
  sprite.setTexture(texture,true);
  sprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
  sprite.setPosition(x,y);

  speed = 1;
  velocity = 20;


}
