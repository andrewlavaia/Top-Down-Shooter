
#include "projectile.h"

Projectile::Projectile(Type t, double x, double y, Orientation::Type o)
{
  type = t;
  orientation = o;

  // Default Weapon Settings
  speed = 20;
  range = 500;
  damage = 1;

  position.x = x;
  position.y = y;

  distance_travelled = 0;
  directions.clear();

  //change texture based on type
  sf::Texture texture;
  texture.create(5,5);
  defaultAnimation = CreateAnimation(texture,5,5,1);
  setCurrentAnimation(defaultAnimation);
  animatedSprite.play(*getCurrentAnimation());
  animatedSprite.setLooped(true);
  //animatedSprite.setFrameTime(sf::seconds(0.16));
  animatedSprite.setColor(sf::Color(255,255,0));
  animatedSprite.setPosition(position.x, position.y);
  animatedSprite.hitbox.setPosition(position.x, position.y);

  directions.push_back(Direction(orientation, range, speed, false));

  directions_it = directions.begin();
}

void Projectile::collideWithEntity(const AnimatedEntity& a)
{
  if (checkCollision(a) == false)
    return;

  if(typeid(a) == typeid(Hero))
  {
   destroy_flag = true;
  }
  else if(typeid(a) == typeid(NPC))
  {
    destroy_flag = true;
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
    destroy_flag = true; // will automatically collide with anything in top left of screen before moving
  }

}
