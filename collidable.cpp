#include "collidable.h"


Collidable::Collidable(Type t, double x, double y, double width, double height)
{
  type = t;
  position.x = x;
  position.y = y;

  sf::Texture texture;
  texture.create(width, height);
  sprite.setTexture(texture); // assign empty texture
  //CRASH IF BELOW IS ACTIVE - window.draw method arithmetic error?
  //sprite.setColor(sf::Color(0, 0, 255, 100)); // semi-transparent blue hitbox
  //sprite.setOrigin(width/2, height/2);
  sprite.setPosition(position.x,position.y);

  switch(type)
  {
    case Collidable::SubwayDoor :
      sprite.setColor(sf::Color(0, 255, 0, 100)); // semi-transparent green hitbox
      break;

    case Collidable::SubwayPlatform :
      sprite.setColor(sf::Color(0, 0, 255, 100)); // semi-transparent blue hitbox
      break;

    case Collidable::SubwayRail :
      sprite.setColor(sf::Color(0, 255, 255, 100)); // semi-transparent teal hitbox
      break;

    case Collidable::ImmovableObject :
      sprite.setColor(sf::Color(255, 0, 255, 100)); // semi-transparent purple hitbox
      break;
  }

}

