#include "npc.h"

NPC::NPC()
{
  x = 200;
  y = 200;

  if (!texture.loadFromFile("character-sprite-map.gif"))
  {
      // error...
  }

  texture.setSmooth(true);
  sprite.setTexture(texture,true);
  sprite.setTextureRect(sf::IntRect(167, 20, 20, 20));
  sprite.setPosition(x,y);

  speed = .5;
  velocity = 5;

  collision_flag = false;


}
