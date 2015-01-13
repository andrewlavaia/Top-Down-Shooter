
#include "weapon.h"

Weapon::Weapon(Type t)
  : attack1(Attack::Push), // default initialization
    attack2(Attack::Push)  // default initialization
{
  type = t;

  // Default Weapon Settings
  attack_modifier = 1;
  durability = 5;
  range = 1;
  position.x = rand()%1024;    //random number generator : rand()%(max-min+1) + min
  position.y = rand()%768;

  distance_travelled = 0;
  directions.clear();


  sf::Texture texture;
  texture.create(10,10);
  defaultAnimation = CreateAnimation(texture,10,10,1);
  setCurrentAnimation(defaultAnimation);
  animatedSprite.play(*getCurrentAnimation());
  animatedSprite.setLooped(true);
  animatedSprite.setFrameTime(sf::seconds(0.16));
  animatedSprite.setColor(sf::Color(255,0,0)); // red box


  switch(type)
  {
    case Weapon::Hands :
      attack_modifier = 1;
      range = 1;
      attack1.setType(Attack::Push);
      attack2.setType(Attack::Kick);
      directions.push_back(Direction(Orientation::S, 1, 0)); //initialize
      break;

    case Weapon::Pole :
      attack_modifier = 3;
      range = 3;
      attack1.setType(Attack::Push);
      attack2.setType(Attack::Smash);
      //directions.push_back(Direction(Orientation::S, 1, 0)); //initialize
      break;

    case Weapon::Lasso :
      attack_modifier = 1;
      range = 10;
      attack1.setType(Attack::Push);
      attack2.setType(Attack::Smash);
      directions.push_back(Direction(Orientation::S, 100, 1)); //initialize
      directions.push_back(Direction(Orientation::N, 100, 1)); //initialize
      break;
  }

  directions_it = directions.begin();
}


void Weapon::collideWithEntity(const AnimatedEntity& a)
{
  if (checkCollision(a) == false)
    return;

  if(typeid(a) == typeid(Hero))
  {
    // --durability;
  }
  else if(typeid(a) == typeid(NPC))
  {
    // --durability;
  }
  else if(typeid(a) == typeid(Weapon))
  {
    // do nothing
  }
  else if(typeid(a) == typeid(Projectile))
  {
    // do nothing
  }
  else if(typeid(a) == typeid(Collidable))
  {
    // --durability;
  }

}

