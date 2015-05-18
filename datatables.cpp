
#include "datatables.h"


DataTable::DataTable()
  : HeroTable(initializeHeroData()),
    NPCTable(initializeNPCData()),
    WeaponTable(initializeWeaponData()),
    CollidableTable(initializeCollidableData()),
    ProjectileTable(initializeProjectileData())
{

}

std::vector<HeroData> DataTable::initializeHeroData()
{
  std::vector<HeroData> data(Hero::TypeCount);

  data[Hero::Bob].hitpoints = 10;
  data[Hero::Bob].speed = 10;
  data[Hero::Bob].power = 1;
  data[Hero::Bob].idleAnimationID = Animations::Hero_Run;
  data[Hero::Bob].moveAnimationID = Animations::Hero_Run;
  data[Hero::Bob].dieAnimationID = Animations::Hero_Run;
  data[Hero::Bob].deadAnimationID = Animations::Hero_Run;
  data[Hero::Bob].attackedAnimationID = Animations::Hero_Run;
  data[Hero::Bob].grabAnimationID = Animations::Hero_Grab;
  data[Hero::Bob].punchAnimationID = Animations::Hero_Punch;
  data[Hero::Bob].origin = sf::Vector2u(29,22);
  data[Hero::Bob].hitboxDimensions = sf::Vector2u(20,20);
  data[Hero::Bob].color = sf::Color::White;

  data[Hero::Joe] = data[Hero::Bob];
  data[Hero::Joe].color = sf::Color::Red;


  return data;

}

std::vector<NPCData> DataTable::initializeNPCData()
{
  std::vector<NPCData> data(NPC::TypeCount);

  data[NPC::Chumba].hitpoints = 10;
  data[NPC::Chumba].speed = 1;
  data[NPC::Chumba].power = 1;
  data[NPC::Chumba].idleAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].moveAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].dieAnimationID = Animations::Hero_Punch;
  data[NPC::Chumba].deadAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].attackedAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].grabbedAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].thrownAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].origin = sf::Vector2u(16,16);
  data[NPC::Chumba].hitboxDimensions = sf::Vector2u(20,20);
  data[NPC::Chumba].color = sf::Color::White;

  data[NPC::Goomba].hitpoints = 10;
  data[NPC::Goomba].speed = 2;
  data[NPC::Goomba].power = 1;
  data[NPC::Goomba].idleAnimationID = Animations::NPC_Run;
  data[NPC::Goomba].moveAnimationID = Animations::NPC_Run;
  data[NPC::Goomba].dieAnimationID = Animations::Hero_Punch;
  data[NPC::Goomba].deadAnimationID = Animations::NPC_Run;
  data[NPC::Goomba].attackedAnimationID = Animations::NPC_Run;
  data[NPC::Goomba].grabbedAnimationID = Animations::NPC_Run;
  data[NPC::Goomba].thrownAnimationID = Animations::Hero_Punch;
  data[NPC::Goomba].origin = sf::Vector2u(16,16);
  data[NPC::Goomba].hitboxDimensions = sf::Vector2u(20,20);
  data[NPC::Goomba].color = sf::Color::Red;

  return data;
}

std::vector<WeaponData> DataTable::initializeWeaponData()
{
  std::vector<WeaponData> data(Weapon::TypeCount);

  data[Weapon::Hands].hitpoints = 10000000; // indestructible
  data[Weapon::Hands].power = 1;
  data[Weapon::Hands].range = 2;
  data[Weapon::Hands].idleAnimationID = Animations::Empty;
  data[Weapon::Hands].moveAnimationID = Animations::Empty;
  data[Weapon::Hands].primaryAttackType = Attack::Standard;
  data[Weapon::Hands].secondaryAttackType = Attack::Standard;
  data[Weapon::Hands].primaryAttackSpeed = 0.5;
  data[Weapon::Hands].secondaryAttackSpeed = 0.5;
  data[Weapon::Hands].ammoType = Projectile::Empty;
  data[Weapon::Hands].ammoCount = 0;

  data[Weapon::Pole].power = 3;
  data[Weapon::Pole].range = 10;
  data[Weapon::Pole].idleAnimationID = Animations::Empty;
  data[Weapon::Pole].moveAnimationID = Animations::Empty;
  data[Weapon::Pole].primaryAttackType = Attack::Standard;
  data[Weapon::Pole].secondaryAttackType = Attack::Standard;
  data[Weapon::Pole].primaryAttackSpeed = 0.5;
  data[Weapon::Pole].secondaryAttackSpeed = 0.5;
  data[Weapon::Pole].ammoType = Projectile::Empty;
  data[Weapon::Pole].ammoCount = 0;

  data[Weapon::Sword].power = 4;
  data[Weapon::Sword].range = 4;
  data[Weapon::Sword].idleAnimationID = Animations::Empty;
  data[Weapon::Sword].moveAnimationID = Animations::Empty;
  data[Weapon::Sword].primaryAttackType = Attack::Standard;
  data[Weapon::Sword].secondaryAttackType = Attack::Standard;
  data[Weapon::Sword].primaryAttackSpeed = 0.3;
  data[Weapon::Sword].secondaryAttackSpeed = 0.3;
  data[Weapon::Sword].ammoType = Projectile::Empty;
  data[Weapon::Sword].ammoCount = 0;

  data[Weapon::Axe].power = 4;
  data[Weapon::Axe].range = 5;
  data[Weapon::Axe].idleAnimationID = Animations::Empty;
  data[Weapon::Axe].moveAnimationID = Animations::Empty;
  data[Weapon::Axe].primaryAttackType = Attack::Standard;
  data[Weapon::Axe].secondaryAttackType = Attack::Standard;
  data[Weapon::Axe].primaryAttackSpeed = 0.4;
  data[Weapon::Axe].secondaryAttackSpeed = 0.4;
  data[Weapon::Axe].ammoType = Projectile::Empty;
  data[Weapon::Axe].ammoCount = 0;

  data[Weapon::Pistol].power = 1;
  data[Weapon::Pistol].range = 2;
  data[Weapon::Pistol].idleAnimationID = Animations::Pistol;
  data[Weapon::Pistol].moveAnimationID = Animations::Pistol;
  data[Weapon::Pistol].primaryAttackType = Attack::Shoot;
  data[Weapon::Pistol].secondaryAttackType = Attack::Standard;
  data[Weapon::Pistol].primaryAttackSpeed = 0.25;
  data[Weapon::Pistol].secondaryAttackSpeed = 0.5;
  data[Weapon::Pistol].ammoType = Projectile::Bullet;
  data[Weapon::Pistol].ammoCount = 25;
  data[Weapon::Pistol].origin = sf::Vector2u(16,16);
  data[Weapon::Pistol].hitboxDimensions = sf::Vector2u(10,10);

  data[Weapon::Shotgun].power = 2;
  data[Weapon::Shotgun].range = 3;
  data[Weapon::Shotgun].idleAnimationID = Animations::Pistol;
  data[Weapon::Shotgun].moveAnimationID = Animations::Pistol;
  data[Weapon::Shotgun].primaryAttackType = Attack::Shoot;
  data[Weapon::Shotgun].secondaryAttackType = Attack::Standard;
  data[Weapon::Shotgun].primaryAttackSpeed = 0.5;
  data[Weapon::Shotgun].secondaryAttackSpeed = 0.5;
  data[Weapon::Shotgun].ammoType = Projectile::BuckShot;
  data[Weapon::Shotgun].ammoCount = 25;
  data[Weapon::Shotgun].origin = sf::Vector2u(16,16);
  data[Weapon::Shotgun].hitboxDimensions = sf::Vector2u(10,10);

  data[Weapon::Rifle].power = 2;
  data[Weapon::Rifle].range = 3;
  data[Weapon::Rifle].idleAnimationID = Animations::Pistol;
  data[Weapon::Rifle].moveAnimationID = Animations::Pistol;
  data[Weapon::Rifle].primaryAttackType = Attack::Shoot;
  data[Weapon::Rifle].secondaryAttackType = Attack::Standard;
  data[Weapon::Rifle].primaryAttackSpeed = 0.5;
  data[Weapon::Rifle].secondaryAttackSpeed = 0.5;
  data[Weapon::Rifle].ammoType = Projectile::Bullet;
  data[Weapon::Rifle].ammoCount = 25;
  data[Weapon::Rifle].origin = sf::Vector2u(16,16);
  data[Weapon::Rifle].hitboxDimensions = sf::Vector2u(10,10);

  data[Weapon::SMG].power = 1;
  data[Weapon::SMG].range = 2;
  data[Weapon::SMG].idleAnimationID = Animations::Pistol;
  data[Weapon::SMG].moveAnimationID = Animations::Pistol;
  data[Weapon::SMG].primaryAttackType = Attack::Shoot;
  data[Weapon::SMG].secondaryAttackType = Attack::Standard;
  data[Weapon::SMG].primaryAttackSpeed = 0.10;
  data[Weapon::SMG].secondaryAttackSpeed = 0.5;
  data[Weapon::SMG].ammoType = Projectile::Bullet;
  data[Weapon::SMG].ammoCount = 100;
  data[Weapon::SMG].origin = sf::Vector2u(16,16);
  data[Weapon::SMG].hitboxDimensions = sf::Vector2u(10,10);

  data[Weapon::RocketLauncher].power = 2;
  data[Weapon::RocketLauncher].range = 3;
  data[Weapon::RocketLauncher].idleAnimationID = Animations::Pistol;
  data[Weapon::RocketLauncher].moveAnimationID = Animations::Pistol;
  data[Weapon::RocketLauncher].primaryAttackType = Attack::Shoot;
  data[Weapon::RocketLauncher].secondaryAttackType = Attack::Standard;
  data[Weapon::RocketLauncher].primaryAttackSpeed = 1.0;
  data[Weapon::RocketLauncher].secondaryAttackSpeed = 0.5;
  data[Weapon::RocketLauncher].ammoType = Projectile::Rocket;
  data[Weapon::RocketLauncher].ammoCount = 4;
  data[Weapon::RocketLauncher].origin = sf::Vector2u(16,16);
  data[Weapon::RocketLauncher].hitboxDimensions = sf::Vector2u(10,10);

  return data;
}

std::vector<CollidableData> DataTable::initializeCollidableData()
{
  std::vector<CollidableData> data(Collidable::TypeCount);

  data[Collidable::Indestructible].hitpoints = 10000000;
  data[Collidable::Indestructible].speed = 0;
  data[Collidable::Indestructible].power = 0;
  data[Collidable::Indestructible].idleAnimationID = Animations::Grass;
  data[Collidable::Indestructible].color = sf::Color::White;

  data[Collidable::Destructible] = data[Collidable::Indestructible];
  data[Collidable::Exit] = data[Collidable::Indestructible];

  return data;
}

std::vector<ProjectileData> DataTable::initializeProjectileData()
{
  std::vector<ProjectileData> data(Projectile::TypeCount);

  // Empty Projectile type needed for weapons that do not fire projectiles
  data[Projectile::Empty].hitpoints = 0;
  data[Projectile::Empty].speed = 0;
  data[Projectile::Empty].power = 0;
  data[Projectile::Empty].range = 0;
  data[Projectile::Empty].moveAnimationID = Animations::Empty;
  data[Projectile::Empty].dieAnimationID = Animations::Empty;
  data[Projectile::Empty].origin = sf::Vector2u(0,0);
  data[Projectile::Empty].hitboxDimensions = sf::Vector2u(0,0);

  data[Projectile::Bullet].speed = 20.0;
  data[Projectile::Bullet].power = 1.0;
  data[Projectile::Bullet].range = 500;
  data[Projectile::Bullet].moveAnimationID = Animations::Bullet;
  data[Projectile::Bullet].dieAnimationID = Animations::Bullet;

  data[Projectile::BuckShot].speed = 20.0;
  data[Projectile::BuckShot].power = 0.5;
  data[Projectile::BuckShot].range = 500;
  data[Projectile::BuckShot].moveAnimationID = Animations::Bullet;
  data[Projectile::BuckShot].dieAnimationID = Animations::Bullet;

  data[Projectile::Rocket].speed = 10.0;
  data[Projectile::Rocket].power = 5.0;
  data[Projectile::Rocket].range = 500;
  data[Projectile::Rocket].moveAnimationID = Animations::Bullet;
  data[Projectile::Rocket].dieAnimationID = Animations::Bullet;

  return data;
}
