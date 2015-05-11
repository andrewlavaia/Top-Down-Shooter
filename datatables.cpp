
#include "datatables.h"


DataTable::DataTable()
  : NPCTable(initializeNPCData()),
    WeaponTable(initializeWeaponData()),
    CollidableTable(initializeCollidableData()),
    ProjectileTable(initializeProjectileData())
{

}

std::vector<NPCData> DataTable::initializeNPCData()
{
  std::vector<NPCData> data(NPC::TypeCount);

  data[NPC::Chumba].hitpoints = 10;
  data[NPC::Chumba].speed = 2;
  data[NPC::Chumba].power = 1;
  data[NPC::Chumba].idleAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].moveAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].dieAnimationID = Animations::Hero_Punch;
  data[NPC::Chumba].deadAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].attackedAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].grabbedAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].thrownAnimationID = Animations::NPC_Run;
  data[NPC::Chumba].origin = sf::Vector2u(16,16);
  data[NPC::Chumba].hitboxDimensions = sf::Vector2u(10,10);
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
  data[NPC::Goomba].thrownAnimationID = Animations::NPC_Run;
  data[NPC::Goomba].origin = sf::Vector2u(16,16);
  data[NPC::Goomba].hitboxDimensions = sf::Vector2u(10,10);
  data[NPC::Goomba].color = sf::Color::Red;

  return data;
}

std::vector<WeaponData> DataTable::initializeWeaponData()
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

std::vector<CollidableData> DataTable::initializeCollidableData()
{
  std::vector<CollidableData> data(Collidable::TypeCount);

  data[Collidable::Indestructible].hitpoints = 10;
  data[Collidable::Indestructible].speed = 2;
  data[Collidable::Indestructible].power = 1;
  data[Collidable::Indestructible].idleAnimationID = Animations::Grass;
  data[Collidable::Indestructible].origin = sf::Vector2u(16,16);
  data[Collidable::Indestructible].hitboxDimensions = sf::Vector2u(10,10);
  data[Collidable::Indestructible].color = sf::Color::White;

  data[Collidable::Destructible] = data[Collidable::Indestructible];
  data[Collidable::Exit] = data[Collidable::Indestructible];

  return data;
}

std::vector<ProjectileData> DataTable::initializeProjectileData()
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

  data[Projectile::BuckShot] = data[Projectile::Bullet];

  return data;
}
