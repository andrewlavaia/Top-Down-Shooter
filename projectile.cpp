
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


  sf::Texture hitbox_texture;
  hitbox_texture.create(5,5);
  animatedSprite.hitbox.setTexture(hitbox_texture); // assign empty texture
  animatedSprite.hitbox.setColor(sf::Color(255,0,0,100)); // semi-transparent red hitbox
  animatedSprite.hitbox.setOrigin(2.5, 2.5);
  animatedSprite.hitbox.setPosition(position.x, position.y);

  AddDirection(orientation, range, speed, false);

  //directions_it = directions.begin();
}

void Projectile::collideWithEntity(const AnimatedEntity& a)
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
