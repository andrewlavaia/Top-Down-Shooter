
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

namespace
{
//const std::vector<WeaponData> Table = initializeWeaponData();
}

Weapon::Weapon(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data, double x, double y)
  : AnimatedEntity(AnimatedEntity::WeaponType),
    type(t),
    idleAnimation(animations.get(Animations::Pistol)),
    moveAnimation(animations.get(Animations::Pistol)),
    primaryAttackAnimation(animations.get(Animations::Empty)),
    secondaryAttackAnimation(animations.get(Animations::Empty)),
    primaryAttack(std::unique_ptr<Attack>(new Attack(Attack::Standard))),
    secondaryAttack(std::unique_ptr<Attack>(new Attack(Attack::Standard))),
    ammoType(std::unique_ptr<Projectile>(new Projectile(data.WeaponTable[t].ammoType, animations, data)))
{

  // Default Weapon Settings
  range = 2;
  // durability = 5;

  //std::cout<<Table[type].hitpoints<<std::endl;


  position.x = x; //rand()%1024;    //random number generator : rand()%(max-min+1) + min
  position.y = y; //rand()%768;

  //sf::Texture texture;
  //texture.create(10,10);
  //moveAnimation = CreateAnimation(texture,10,10,1);
  //setCurrentAnimation(moveAnimation);
  animatedSprite.play(moveAnimation);
  animatedSprite.setLooped(true);
  //animatedSprite.setFrameTime(sf::seconds(0.16));
  //animatedSprite.setColor(sf::Color(255,150,0)); // orange box
  animatedSprite.setPosition(position.x, position.y);

  // set hitbox for collision testing
  setHitbox(*animations.get(Animations::Hitbox).getSpriteSheet(), 10,10);
  //hitbox.setOrigin(animatedSprite.getLocalBounds().width/2,animatedSprite.getLocalBounds().height); // need to override default origin setting so that weapon gets scaled properly

  double scale_factor = 0.50;
  animatedSprite.setScale(scale_factor,scale_factor);

  switch(type)
  {
    case Weapon::Hands :
      range = 2;
      //primaryAttackAnimation = std::make_shared<Animation>(animations.get(Animations::Hero_Punch));
      //secondaryAttackAnimation = CreateAnimation(texture,50,50,1);
      break;

    case Weapon::Pole :
      setPower(3);
      range = 10;
      //primaryAttackAnimation = CreateAnimation(texture,10,10,1);
      //secondaryAttackAnimation = CreateAnimation(texture,50,50,1);
      break;

    case Weapon::Pistol :
      primaryAttack = std::move(std::unique_ptr<Attack>(new Attack(Attack::Shoot, 0.25)));
      ammoType = std::move(std::unique_ptr<Projectile>(new Projectile(Projectile::Bullet, animations, data)));
      //primaryAttackAnimation = CreateAnimation(texture,10,10,1);
      //secondaryAttackAnimation = CreateAnimation(texture,50,50,1);
      break;

    case Weapon::Shotgun :
      primaryAttack = std::move(std::unique_ptr<Attack>(new Attack(Attack::Shoot, 0.5)));
      ammoType = std::move(std::unique_ptr<Projectile>(new Projectile(Projectile::BuckShot, animations, data)));
      //primaryAttackAnimation = CreateAnimation(texture,10,10,1);
      //secondaryAttackAnimation = CreateAnimation(texture,50,50,1);
      break;

    case Weapon::SMG :
      primaryAttack = std::move(std::unique_ptr<Attack>(new Attack(Attack::Shoot, 0.10)));
      ammoType = std::move(std::unique_ptr<Projectile>(new Projectile(Projectile::Bullet, animations, data)));
      //primaryAttackAnimation = CreateAnimation(texture,10,10,1);
      //secondaryAttackAnimation = CreateAnimation(texture,50,50,1);
      break;

    case Weapon::RocketLauncher :
      primaryAttack = std::move(std::unique_ptr<Attack>(new Attack(Attack::Shoot, 1.0)));
      ammoType = std::move(std::unique_ptr<Projectile>(new Projectile(Projectile::Rocket, animations, data)));
      //primaryAttackAnimation = CreateAnimation(texture,10,10,1);
      //secondaryAttackAnimation = CreateAnimation(texture,50,50,1);
      break;
  }
}


void Weapon::collideWithEntity(const AnimatedEntity& a, sf::Time dt)
{
  if (checkCollision(a) == false)
    return;

  switch(a.getParentType())
  {
    case AnimatedEntity::HeroType :
      break;

    case AnimatedEntity::NPCType :
      break;

    case AnimatedEntity::WeaponType :
      break;

    case AnimatedEntity::ProjectileType :
      break;

    case AnimatedEntity::CollidableType :
      break;
  }

/*
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
*/
}

void Weapon::playAnimation()
{
  switch(getStatus())
  {
    case AnimatedEntity::Idle :
      animatedSprite.play(idleAnimation);
      //animatedSprite.pause(); // or animatedSprite.stop() to revert back to first frame
      break;

    case AnimatedEntity::Moving :
      animatedSprite.play(moveAnimation);
      break;
  }
}

