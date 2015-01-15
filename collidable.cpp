#include "collidable.h"


Collidable::Collidable(Type t, int x, int y, int width, int height)
{
  type = t;
  position.x = x + width/2;
  position.y = y + height/2;

  //change texture based on type
  sf::Texture texture;
  texture.create(width,height);
  defaultAnimation = CreateAnimation(texture,width,height,1);
  setCurrentAnimation(defaultAnimation);
  animatedSprite.play(*getCurrentAnimation());
  animatedSprite.setLooped(true);
  animatedSprite.setFrameTime(sf::seconds(0.16));
  animatedSprite.setColor(sf::Color(0, 0, 255, 100));

  animatedSprite.setPosition(position.x + width/2, position.y + height/2);
  animatedSprite.setOrigin(width/2, height/2);

  // set hitbox for collision testing
  sf::Texture hitbox_texture;
  hitbox_texture.create(width,height);
  animatedSprite.hitbox.setTexture(hitbox_texture); // assign empty texture 20x20 pixels
  animatedSprite.hitbox.setColor(sf::Color(255,0,0,100)); // semi-transparent red hitbox
  animatedSprite.hitbox.setOrigin(width/2, height/2);

  switch(type)
  {
    case Collidable::SubwayDoor :
      animatedSprite.setColor(sf::Color(0, 255, 0, 100)); // semi-transparent green hitbox
      break;

    case Collidable::SubwayPlatform :
      animatedSprite.setColor(sf::Color(0, 0, 255, 100)); // semi-transparent blue hitbox
      break;

    case Collidable::SubwayRail :
      animatedSprite.setColor(sf::Color(0, 255, 255, 100)); // semi-transparent teal hitbox
      break;

    case Collidable::ImmovableObject :
      animatedSprite.setColor(sf::Color(255, 0, 255, 100)); // semi-transparent purple hitbox
      break;
  }

}

void Collidable::collideWithEntity(const AnimatedEntity& a)
{
  if (checkCollision(a) == false)
    return;

  if(typeid(a) == typeid(Hero))
  {
    // do nothing
  }
  else if(typeid(a) == typeid(NPC))
  {
    // do nothing
  }
  else if(typeid(a) == typeid(Weapon))
  {
    // take damage
  }
  else if(typeid(a) == typeid(Projectile))
  {
    // take damage
  }
  else if(typeid(a) == typeid(Collidable))
  {
    // not possible?
  }

}
