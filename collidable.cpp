#include "collidable.h"


Collidable::Collidable(Type t, int x, int y, int width, int height, ResourceHolder<Animation, Animations::ID>& animations)
{
  type = t;

  position.x = x + width/2;
  position.y = y + height/2;

  //change texture based on type
  sf::Texture texture;
  texture.create(width,height);
  moveAnimation = CreateAnimation(texture,width,height,1);
  setCurrentAnimation(moveAnimation);
  animatedSprite.play(*getCurrentAnimation());
  animatedSprite.setLooped(true);
  animatedSprite.setFrameTime(sf::seconds(0.16));
  animatedSprite.setColor(sf::Color(0, 0, 255, 100));

  animatedSprite.setPosition(position.x + width/2, position.y + height/2);
  animatedSprite.setOrigin(width/2, height/2);

  // FIX THIS SO THAT TEXTURE STAYS IN SCOPE FOR OBJECT LIFETIME
  // set hitbox for collision testing
  /*
  sf::Texture hitbox_texture;
  hitbox_texture.create(width, height);
  animatedSprite.hitbox.setTexture(hitbox_texture);
  animatedSprite.hitbox.setColor(sf::Color(255,0,0,100)); // semi-transparent red hitbox
  animatedSprite.hitbox.setOrigin(width/2, height/2);
  animatedSprite.hitbox.setPosition(animatedSprite.getPosition());
  */

  animatedSprite.setHitbox(width, height);

  switch(type)
  {
    case Collidable::Exit :
      animatedSprite.setColor(sf::Color(0, 255, 0, 100)); // semi-transparent green hitbox
      setHitPoints(1000000000); // virtually indestructible
      break;

    case Collidable::Indestructible :
      animatedSprite.setColor(sf::Color(0, 255, 255, 100)); // semi-transparent teal hitbox
      setHitPoints(1000000000); // virtually indestructible
      break;

    //replace with specific types of destructible objects
    case Collidable::Destructible :
      animatedSprite.setColor(sf::Color(0, 0, 255, 100)); // semi-transparent blue hitbox
      break;
  }

}

void Collidable::collideWithEntity(const AnimatedEntity& a, sf::Time dt)
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
    TakeDamage(a.getPower());
  }
  else if(typeid(a) == typeid(Projectile))
  {
    TakeDamage(a.getPower());
  }
  else if(typeid(a) == typeid(Collidable))
  {
    // not possible?
  }

}
