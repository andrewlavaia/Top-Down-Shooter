
#include "weapon.h"


/* ANIMATION TYPES
Punch,        // default primary
Kick,         // default secondary
Bite,
MeleeBash1H   // (hammer, pistol whip, etc)
MeleeBash2H,  // (sledgehammer, rifle butt, etc)
MeleePoke,    // (pitch fork)
MeleeSlash,   // (swords, knives, etc)
PistolShot,
ShotgunShot,
RifleShot,
SMGShot,
BowShot,
Explosive,    // (rocket launcher, grenade, etc)
Stun,         // (taser, etc)
*/

Weapon::Weapon(Type t, double x, double y)
  : primaryAttackAnimation(nullptr), // default initialization
    secondaryAttackAnimation(nullptr)  // default initialization
{
  type = t;

  // Default Weapon Settings
  damage_modifier = 1;
  durability = 5;
  range = 2;

  position.x = x; //rand()%1024;    //random number generator : rand()%(max-min+1) + min
  position.y = y; //rand()%768;


  sf::Texture texture;
  texture.create(10,10);
  moveAnimation = CreateAnimation(texture,10,10,1);
  setCurrentAnimation(moveAnimation);
  animatedSprite.play(*getCurrentAnimation());
  animatedSprite.setLooped(true);
  //animatedSprite.setFrameTime(sf::seconds(0.16));
  animatedSprite.setColor(sf::Color(255,150,0)); // orange box
  animatedSprite.setPosition(position.x, position.y);


  // set hitbox for collision testing
  sf::Texture hitbox_texture;
  hitbox_texture.create(10,10);
  animatedSprite.hitbox.setTexture(hitbox_texture); // assign empty texture
  animatedSprite.hitbox.setColor(sf::Color(255,0,0,100)); // semi-transparent red hitbox
  animatedSprite.hitbox.setOrigin(5, 10);
  animatedSprite.hitbox.setPosition(position.x, position.y);


  switch(type)
  {
    case Weapon::Hands :
      damage_modifier = 1;
      range = 2;
      primaryAttackAnimation = CreateAnimation(texture,10,10,1);
      secondaryAttackAnimation = CreateAnimation(texture,50,50,1);
      //attack1(new Attack(Attack::Push));
//      attack2.setType(Attack::Kick);
      break;

    case Weapon::Pole :
      damage_modifier = 3;
      range = 5;
//      attack1.setType(Attack::Push);
//      attack2.setType(Attack::Smash);
      break;


    case Weapon::Lasso:
      damage_modifier = 1;
      range = 10;

//      attack1.setType(Attack::Push);
//      attack2.setType(Attack::Smash);

      break;

  }

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

