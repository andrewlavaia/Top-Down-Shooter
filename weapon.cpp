
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
  : primaryAttackAnimation(nullptr),
    secondaryAttackAnimation(nullptr),
    ammoType(nullptr)
{
  type = t;

  // Default Weapon Settings
  primaryAttackType = AttackType::Standard;
  secondaryAttackType = AttackType::Standard;
  range = 2;
  // durability = 5;


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
  animatedSprite.setHitbox(10,10);
  //animatedSprite.hitbox.setOrigin(animatedSprite.getLocalBounds().width/2,animatedSprite.getLocalBounds().height); // need to override default origin setting so that weapon gets scaled properly

  switch(type)
  {
    case Weapon::Hands :
      range = 2;
      primaryAttackAnimation = CreateAnimation(texture,10,10,1);
      secondaryAttackAnimation = CreateAnimation(texture,50,50,1);
      break;

    case Weapon::Pole :
      setPower(3);
      range = 5;
      primaryAttackAnimation = CreateAnimation(texture,10,10,1);
      secondaryAttackAnimation = CreateAnimation(texture,50,50,1);
      break;

    case Weapon::Lasso :
      range = 10;
      primaryAttackAnimation = CreateAnimation(texture,10,10,1);
      secondaryAttackAnimation = CreateAnimation(texture,50,50,1);
      break;

    case Weapon::Pistol :
      primaryAttackType = AttackType::Shoot;
      ammoType = std::move(std::unique_ptr<Projectile>(new Projectile(Projectile::Bullet)));
      range = 10;
      primaryAttackAnimation = CreateAnimation(texture,10,10,1);
      secondaryAttackAnimation = CreateAnimation(texture,50,50,1);
      break;

    case Weapon::RocketLauncher :
      primaryAttackType = AttackType::Shoot;
      ammoType = std::move(std::unique_ptr<Projectile>(new Projectile(Projectile::Rocket)));
      range = 10;
      primaryAttackAnimation = CreateAnimation(texture,10,10,1);
      secondaryAttackAnimation = CreateAnimation(texture,50,50,1);
      break;
  }
}


void Weapon::collideWithEntity(const AnimatedEntity& a, sf::Time dt)
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

