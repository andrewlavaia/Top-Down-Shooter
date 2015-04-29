
#include "datatables.h"

std::vector<NPCData> initializeNPCData()
{
  std::vector<NPCData> data(NPC::TypeCount);

  data[NPC::Chumba].hitpoints = 10;
  data[NPC::Chumba].speed = 2;
  data[NPC::Chumba].power = 1;
  data[NPC::Chumba].moveAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].deadAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].attackedAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].grabbedAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].thrownAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].origin = sf::Vector2u(16,16);
  data[NPC::Chumba].hitboxDimensions = sf::Vector2u(10,10);

  data[NPC::Goomba] = data[NPC::Chumba];
  data[NPC::Goomba].color = sf::Color::Red;

  return data;
}

std::vector<WeaponData> initializeWeaponData()
{
  std::vector<WeaponData> data(Weapon::TypeCount);

  data[Weapon::Hands].hitpoints = 10;
  data[Weapon::Hands].speed = 2;
  data[Weapon::Hands].power = 1;
  data[Weapon::Hands].idleAnimationID = Animations::Empty;
  data[Weapon::Hands].moveAnimationID = Animations::Empty;
  data[Weapon::Hands].primaryAttackType = Attack::Standard;
  data[Weapon::Hands].secondaryAttackType = Attack::Standard;
  data[Weapon::Hands].primaryAttackSpeed = 0.5;
  data[Weapon::Hands].secondaryAttackSpeed = 0.5;
  data[Weapon::Hands].ammoType = Projectile::Empty;
  data[Weapon::Hands].range = 2;

  data[Weapon::Pistol].hitpoints = 10;
  data[Weapon::Pistol].speed = 2;
  data[Weapon::Pistol].power = 1;
  data[Weapon::Pistol].idleAnimationID = Animations::Pistol;
  data[Weapon::Pistol].moveAnimationID = Animations::Pistol;
  data[Weapon::Pistol].primaryAttackType = Attack::Shoot;
  data[Weapon::Pistol].secondaryAttackType = Attack::Standard;
  data[Weapon::Pistol].primaryAttackSpeed = 0.5;
  data[Weapon::Pistol].secondaryAttackSpeed = 0.5;
  data[Weapon::Pistol].ammoType = Projectile::Bullet;
  data[Weapon::Pistol].origin = sf::Vector2u(16,16);
  data[Weapon::Pistol].hitboxDimensions = sf::Vector2u(10,10);
  data[Weapon::Pistol].range = 2;

  data[Weapon::RocketLauncher] = data[Weapon::Pistol];
  data[Weapon::Rifle] = data[Weapon::Pistol];
  data[Weapon::SMG] = data[Weapon::Pistol];


  return data;
}

std::vector<CollidableData> initializeCollidableData()
{
  std::vector<CollidableData> data(Collidable::TypeCount);

  data[Collidable::Destructible].hitpoints = 10;
  data[Collidable::Destructible].speed = 2;
  data[Collidable::Destructible].power = 1;
  data[Collidable::Destructible].idleAnimationID = Animations::Grass;
  data[Collidable::Destructible].origin = sf::Vector2u(16,16);
  data[Collidable::Destructible].hitboxDimensions = sf::Vector2u(10,10);

  data[Collidable::Indestructible] = data[Collidable::Destructible];
  data[Collidable::Exit] = data[Collidable::Destructible];

  return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
  std::vector<ProjectileData> data(Projectile::TypeCount);

  data[Projectile::Empty].hitpoints = 0;
  data[Projectile::Empty].speed = 0;
  data[Projectile::Empty].power = 0;
  data[Projectile::Empty].moveAnimationID = Animations::Empty;
  data[Projectile::Empty].dieAnimationID = Animations::Empty;
  data[Projectile::Empty].origin = sf::Vector2u(0,0);
  data[Projectile::Empty].hitboxDimensions = sf::Vector2u(0,0);

  data[Projectile::Bullet].hitpoints = 10;
  data[Projectile::Bullet].speed = 2;
  data[Projectile::Bullet].power = 1;
  data[Projectile::Bullet].moveAnimationID = Animations::Bullet;
  data[Projectile::Bullet].dieAnimationID = Animations::Bullet;
  data[Projectile::Bullet].origin = sf::Vector2u(16,16);
  data[Projectile::Bullet].hitboxDimensions = sf::Vector2u(10,10);

  return data;
}
