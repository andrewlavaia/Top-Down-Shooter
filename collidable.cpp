#include "collidable.h"
#include "datatables.h"

namespace
{
  const std::vector<CollidableData> Table = initializeCollidableData();
}

Collidable::Collidable(Type t, double x, double y, double width, double height, const ResourceHolder<Animation, Animations::ID>& animations)
  : idleAnimation(animations.get(Animations::Grass))
{
  type = t;

  position.x = x + width/2;
  position.y = y + height/2;

  //change texture based on type
  sf::Texture texture;
  texture.create(width,height);
  //moveAnimation = CreateAnimation(texture,width,height,1);
  //setCurrentAnimation(moveAnimation);
  //animatedSprite.play(*getCurrentAnimation());
  animatedSprite.play(idleAnimation);
  animatedSprite.setLooped(true);
  animatedSprite.setFrameTime(sf::seconds(0.16));
  //animatedSprite.setColor(sf::Color(0, 0, 255, 100));

  animatedSprite.setScale(width/idleAnimation.getSpriteSheet()->getSize().x,
                          height/idleAnimation.getSpriteSheet()->getSize().y);


  animatedSprite.setPosition(position.x + width/2, position.y + height/2);
  animatedSprite.setOrigin(width/2, height/2);

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

void Collidable::playAnimation()
{
  switch(getStatus())
  {
    case AnimatedEntity::Idle :
      animatedSprite.play(idleAnimation); // or animatedSprite.stop() to revert back to first frame
      break;

  }
}
