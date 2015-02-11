
#include "projectile.h"

Projectile::Projectile(Type t, double x, double y, Orientation::Type o)


{
  type = t;
  orientation = o;

  // Default Weapon Settings
  setSpeed(20);
  range = 500;

  position.x = x;
  position.y = y;


  //change texture based on type
  sf::Texture texture;
  texture.create(5,5);
  moveAnimation = CreateAnimation(texture,5,5,1);

  setCurrentAnimation(moveAnimation);
  animatedSprite.play(*getCurrentAnimation());
  animatedSprite.setLooped(true);
  //animatedSprite.setFrameTime(sf::seconds(0.16));
  animatedSprite.setColor(sf::Color(255,255,0));
  animatedSprite.setPosition(position.x, position.y);

  animatedSprite.setHitbox(5,5);


  switch(type)
  {
    case Projectile::Bullet :
      break;

    case Projectile::BuckShot :
      setPower(0.5);
      animatedSprite.setHitbox(2,2);
      moveAnimation = CreateAnimation(texture,2,2,1);
      setCurrentAnimation(moveAnimation);
      animatedSprite.play(*getCurrentAnimation());
      break;

    case Projectile::Rocket :
      setPower(5);
      setSpeed(10);
      break;
  }

  AddDirection(orientation, range, getSpeed(), false);

}

void Projectile::collideWithEntity(const AnimatedEntity& a, sf::Time dt)
{
  if (checkCollision(a) == false)
    return;

  if(typeid(a) == typeid(Hero))
  {
    Destroy();
  }
  else if(typeid(a) == typeid(NPC))
  {
    Destroy();
  }
  else if(typeid(a) == typeid(Weapon))
  {
    // do nothing?
  }
  else if(typeid(a) == typeid(Projectile))
  {
    // do nothing?
  }
  else if(typeid(a) == typeid(Collidable))
  {
    Destroy();
  }

}
