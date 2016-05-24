
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

  data[Hero::Bob].hitpoints = 100;
  data[Hero::Bob].speed = 10;
  data[Hero::Bob].power = 1;
  data[Hero::Bob].idleAnimationID = Animations::Human_1_Idle;
  data[Hero::Bob].moveAnimationID = Animations::Human_1_Run;
  data[Hero::Bob].dieAnimationID = Animations::Human_1_Die;
  data[Hero::Bob].deadAnimationID = Animations::Human_1_Dead;
  data[Hero::Bob].attackedAnimationID = Animations::Human_1_Attacked;
  data[Hero::Bob].grabAnimationID = Animations::Human_1_Grab;
  //data[Hero::Bob].punchAnimationID = Animations::Hero_Punch;
  data[Hero::Bob].hitboxDimensions = sf::Vector2u(35,35);
  data[Hero::Bob].color = sf::Color::White;

  data[Hero::SuitDrew].hitpoints = 10;
  data[Hero::SuitDrew].speed = 10;
  data[Hero::SuitDrew].power = 1;
  data[Hero::SuitDrew].idleAnimationID = Animations::Human_10_Idle;
  data[Hero::SuitDrew].moveAnimationID = Animations::Human_10_Run;
  data[Hero::SuitDrew].dieAnimationID = Animations::Human_10_Die;
  data[Hero::SuitDrew].deadAnimationID = Animations::Human_10_Dead;
  data[Hero::SuitDrew].attackedAnimationID = Animations::Human_10_Attacked;
  data[Hero::SuitDrew].grabAnimationID = Animations::Human_10_Grab;
  //data[Hero::SuitDrew].punchAnimationID = Animations::Hero_Punch;
  data[Hero::SuitDrew].hitboxDimensions = sf::Vector2u(35,35);
  data[Hero::SuitDrew].color = sf::Color::White;

  data[Hero::GeezerHarry].hitpoints = 10;
  data[Hero::GeezerHarry].speed = 10;
  data[Hero::GeezerHarry].power = 1;
  data[Hero::GeezerHarry].idleAnimationID = Animations::Human_11_Idle;
  data[Hero::GeezerHarry].moveAnimationID = Animations::Human_11_Run;
  data[Hero::GeezerHarry].dieAnimationID = Animations::Human_11_Die;
  data[Hero::GeezerHarry].deadAnimationID = Animations::Human_11_Dead;
  data[Hero::GeezerHarry].attackedAnimationID = Animations::Human_11_Attacked;
  data[Hero::GeezerHarry].grabAnimationID = Animations::Human_11_Grab;
  //data[Hero::GeezerHarry].punchAnimationID = Animations::Hero_Punch;
  data[Hero::GeezerHarry].hitboxDimensions = sf::Vector2u(35,35);
  data[Hero::GeezerHarry].color = sf::Color::White;

  data[Hero::DirtyPete].hitpoints = 10;
  data[Hero::DirtyPete].speed = 10;
  data[Hero::DirtyPete].power = 1;
  data[Hero::DirtyPete].idleAnimationID = Animations::Human_12_Idle;
  data[Hero::DirtyPete].moveAnimationID = Animations::Human_12_Run;
  data[Hero::DirtyPete].dieAnimationID = Animations::Human_12_Die;
  data[Hero::DirtyPete].deadAnimationID = Animations::Human_12_Dead;
  data[Hero::DirtyPete].attackedAnimationID = Animations::Human_12_Attacked;
  data[Hero::DirtyPete].grabAnimationID = Animations::Human_12_Grab;
  //data[Hero::DirtyPete].punchAnimationID = Animations::Hero_Punch;
  data[Hero::DirtyPete].hitboxDimensions = sf::Vector2u(35,35);
  data[Hero::DirtyPete].color = sf::Color::White;

  return data;

}

std::vector<NPCData> DataTable::initializeNPCData()
{
  std::vector<NPCData> data(NPC::TypeCount);

  data[NPC::Sheep].hitpoints = 10;
  data[NPC::Sheep].speed = 1;
  data[NPC::Sheep].power = 1;
  data[NPC::Sheep].idleAnimationID = Animations::Sheep_Walk;
  data[NPC::Sheep].moveAnimationID = Animations::Sheep_Walk;
  data[NPC::Sheep].dieAnimationID = Animations::Sheep_Walk;
  data[NPC::Sheep].deadAnimationID = Animations::Sheep_Walk;
  data[NPC::Sheep].attackedAnimationID = Animations::Sheep_Walk;
  data[NPC::Sheep].grabbedAnimationID = Animations::Sheep_Walk;
  data[NPC::Sheep].thrownAnimationID = Animations::Sheep_Walk;
  data[NPC::Sheep].hitboxDimensions = sf::Vector2u(35,35);
  data[NPC::Sheep].color = sf::Color::White;
  data[NPC::Sheep].scaleFactor = 1.0;

  data[NPC::McGinger].hitpoints = 10;
  data[NPC::McGinger].speed = 1;
  data[NPC::McGinger].power = 1;
  data[NPC::McGinger].idleAnimationID = Animations::Human_2_Idle;
  data[NPC::McGinger].moveAnimationID = Animations::Human_2_Walk;
  data[NPC::McGinger].dieAnimationID = Animations::Human_2_Die;
  data[NPC::McGinger].deadAnimationID = Animations::Human_2_Dead;
  data[NPC::McGinger].attackedAnimationID = Animations::Human_2_Attacked;
  data[NPC::McGinger].grabbedAnimationID = Animations::Human_2_Idle;
  data[NPC::McGinger].thrownAnimationID = Animations::Human_2_Idle;
  data[NPC::McGinger].hitboxDimensions = sf::Vector2u(35,35);
  data[NPC::McGinger].color = sf::Color::White;
  data[NPC::McGinger].weapon = Weapon::Rifle;

  data[NPC::BigRick].hitpoints = 10;
  data[NPC::BigRick].speed = 2;
  data[NPC::BigRick].power = 1;
  data[NPC::BigRick].idleAnimationID = Animations::Human_3_Idle;
  data[NPC::BigRick].moveAnimationID = Animations::Human_3_Run;
  data[NPC::BigRick].dieAnimationID = Animations::Human_3_Die;
  data[NPC::BigRick].deadAnimationID = Animations::Human_3_Dead;
  data[NPC::BigRick].attackedAnimationID = Animations::Human_3_Attacked;
  data[NPC::BigRick].grabbedAnimationID = Animations::Human_3_Idle;
  data[NPC::BigRick].thrownAnimationID = Animations::Human_3_Idle;
  data[NPC::BigRick].hitboxDimensions = sf::Vector2u(35,35);
  data[NPC::BigRick].color = sf::Color::White;
  data[NPC::BigRick].weapon = Weapon::SMG;

  data[NPC::UglyAmy].hitpoints = 10;
  data[NPC::UglyAmy].speed = 2;
  data[NPC::UglyAmy].power = 1;
  data[NPC::UglyAmy].idleAnimationID = Animations::Human_4_Idle;
  data[NPC::UglyAmy].moveAnimationID = Animations::Human_4_Run;
  data[NPC::UglyAmy].dieAnimationID = Animations::Human_4_Die;
  data[NPC::UglyAmy].deadAnimationID = Animations::Human_4_Dead;
  data[NPC::UglyAmy].attackedAnimationID = Animations::Human_4_Attacked;
  data[NPC::UglyAmy].grabbedAnimationID = Animations::Human_4_Idle;
  data[NPC::UglyAmy].thrownAnimationID = Animations::Human_4_Idle;
  data[NPC::UglyAmy].hitboxDimensions = sf::Vector2u(35,35);
  data[NPC::UglyAmy].color = sf::Color::White;

  data[NPC::TooCoolJack].hitpoints = 10;
  data[NPC::TooCoolJack].speed = 2;
  data[NPC::TooCoolJack].power = 1;
  data[NPC::TooCoolJack].idleAnimationID = Animations::Human_5_Idle;
  data[NPC::TooCoolJack].moveAnimationID = Animations::Human_5_Run;
  data[NPC::TooCoolJack].dieAnimationID = Animations::Human_5_Die;
  data[NPC::TooCoolJack].deadAnimationID = Animations::Human_5_Dead;
  data[NPC::TooCoolJack].attackedAnimationID = Animations::Human_5_Attacked;
  data[NPC::TooCoolJack].grabbedAnimationID = Animations::Human_5_Idle;
  data[NPC::TooCoolJack].thrownAnimationID = Animations::Human_5_Idle;
  data[NPC::TooCoolJack].hitboxDimensions = sf::Vector2u(35,35);
  data[NPC::TooCoolJack].color = sf::Color::White;

  data[NPC::DeNiro].hitpoints = 10;
  data[NPC::DeNiro].speed = 2;
  data[NPC::DeNiro].power = 1;
  data[NPC::DeNiro].idleAnimationID = Animations::Human_6_Idle;
  data[NPC::DeNiro].moveAnimationID = Animations::Human_6_Run;
  data[NPC::DeNiro].dieAnimationID = Animations::Human_6_Die;
  data[NPC::DeNiro].deadAnimationID = Animations::Human_6_Dead;
  data[NPC::DeNiro].attackedAnimationID = Animations::Human_6_Attacked;
  data[NPC::DeNiro].grabbedAnimationID = Animations::Human_6_Idle;
  data[NPC::DeNiro].thrownAnimationID = Animations::Human_6_Idle;
  data[NPC::DeNiro].hitboxDimensions = sf::Vector2u(35,35);
  data[NPC::DeNiro].color = sf::Color::White;

  data[NPC::Barnaby].hitpoints = 10;
  data[NPC::Barnaby].speed = 2;
  data[NPC::Barnaby].power = 1;
  data[NPC::Barnaby].idleAnimationID = Animations::Human_7_Idle;
  data[NPC::Barnaby].moveAnimationID = Animations::Human_7_Run;
  data[NPC::Barnaby].dieAnimationID = Animations::Human_7_Die;
  data[NPC::Barnaby].deadAnimationID = Animations::Human_7_Dead;
  data[NPC::Barnaby].attackedAnimationID = Animations::Human_7_Attacked;
  data[NPC::Barnaby].grabbedAnimationID = Animations::Human_7_Idle;
  data[NPC::Barnaby].thrownAnimationID = Animations::Human_7_Idle;
  data[NPC::Barnaby].hitboxDimensions = sf::Vector2u(35,35);
  data[NPC::Barnaby].color = sf::Color::White;

  data[NPC::ToughSugar].hitpoints = 10;
  data[NPC::ToughSugar].speed = 2;
  data[NPC::ToughSugar].power = 1;
  data[NPC::ToughSugar].idleAnimationID = Animations::Human_8_Idle;
  data[NPC::ToughSugar].moveAnimationID = Animations::Human_8_Run;
  data[NPC::ToughSugar].dieAnimationID = Animations::Human_8_Die;
  data[NPC::ToughSugar].deadAnimationID = Animations::Human_8_Dead;
  data[NPC::ToughSugar].attackedAnimationID = Animations::Human_8_Attacked;
  data[NPC::ToughSugar].grabbedAnimationID = Animations::Human_8_Idle;
  data[NPC::ToughSugar].thrownAnimationID = Animations::Human_8_Idle;
  data[NPC::ToughSugar].hitboxDimensions = sf::Vector2u(35,35);
  data[NPC::ToughSugar].color = sf::Color::White;

  data[NPC::AmbiguousAlex].hitpoints = 10;
  data[NPC::AmbiguousAlex].speed = 2;
  data[NPC::AmbiguousAlex].power = 1;
  data[NPC::AmbiguousAlex].idleAnimationID = Animations::Human_9_Idle;
  data[NPC::AmbiguousAlex].moveAnimationID = Animations::Human_9_Run;
  data[NPC::AmbiguousAlex].dieAnimationID = Animations::Human_9_Die;
  data[NPC::AmbiguousAlex].deadAnimationID = Animations::Human_9_Dead;
  data[NPC::AmbiguousAlex].attackedAnimationID = Animations::Human_9_Attacked;
  data[NPC::AmbiguousAlex].grabbedAnimationID = Animations::Human_9_Idle;
  data[NPC::AmbiguousAlex].thrownAnimationID = Animations::Human_9_Idle;
  data[NPC::AmbiguousAlex].hitboxDimensions = sf::Vector2u(35,35);
  data[NPC::AmbiguousAlex].color = sf::Color::White;

  data[NPC::BaldingSam].hitpoints = 10;
  data[NPC::BaldingSam].speed = 2;
  data[NPC::BaldingSam].power = 1;
  data[NPC::BaldingSam].idleAnimationID = Animations::Human_13_Idle;
  data[NPC::BaldingSam].moveAnimationID = Animations::Human_13_Run;
  data[NPC::BaldingSam].dieAnimationID = Animations::Human_13_Die;
  data[NPC::BaldingSam].deadAnimationID = Animations::Human_13_Dead;
  data[NPC::BaldingSam].attackedAnimationID = Animations::Human_13_Attacked;
  data[NPC::BaldingSam].grabbedAnimationID = Animations::Human_13_Idle;
  data[NPC::BaldingSam].thrownAnimationID = Animations::Human_13_Idle;
  data[NPC::BaldingSam].hitboxDimensions = sf::Vector2u(35,35);
  data[NPC::BaldingSam].color = sf::Color::White;

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
  data[Weapon::Hands].primaryAttackAnimationID = Animations::Empty;
  data[Weapon::Hands].secondaryAttackAnimationID = Animations::Empty;
  data[Weapon::Hands].primaryAttackType = Attack::Standard;
  data[Weapon::Hands].secondaryAttackType = Attack::Standard;
  data[Weapon::Hands].primaryAttackSpeed = 0.5;
  data[Weapon::Hands].secondaryAttackSpeed = 0.5;
  data[Weapon::Hands].ammoType = Projectile::Empty;
  data[Weapon::Hands].ammoCount = 0;

  data[Weapon::Pistol].power = 1;
  data[Weapon::Pistol].range = 2;
  data[Weapon::Pistol].idleAnimationID = Animations::Pistol;
  data[Weapon::Pistol].moveAnimationID = Animations::Pistol;
  data[Weapon::Pistol].primaryAttackAnimationID = Animations::Pistol;
  data[Weapon::Pistol].secondaryAttackAnimationID = Animations::Pistol;
  data[Weapon::Pistol].primaryAttackType = Attack::Shoot;
  data[Weapon::Pistol].secondaryAttackType = Attack::Standard;
  data[Weapon::Pistol].primaryAttackSpeed = 0.25;
  data[Weapon::Pistol].secondaryAttackSpeed = 0.5;
  data[Weapon::Pistol].ammoType = Projectile::Bullet;
  data[Weapon::Pistol].ammoCount = 25;
  data[Weapon::Pistol].hitboxDimensions = sf::Vector2u(10,10);
  data[Weapon::Pistol].scaleFactor = 0.8;

  data[Weapon::Shotgun].power = 2;
  data[Weapon::Shotgun].range = 3;
  data[Weapon::Shotgun].idleAnimationID = Animations::Shotgun;
  data[Weapon::Shotgun].moveAnimationID = Animations::Shotgun;
  data[Weapon::Shotgun].primaryAttackAnimationID = Animations::Shotgun;
  data[Weapon::Shotgun].secondaryAttackAnimationID = Animations::Shotgun;
  data[Weapon::Shotgun].primaryAttackType = Attack::Shoot;
  data[Weapon::Shotgun].secondaryAttackType = Attack::Standard;
  data[Weapon::Shotgun].primaryAttackSpeed = 0.5;
  data[Weapon::Shotgun].secondaryAttackSpeed = 0.5;
  data[Weapon::Shotgun].ammoType = Projectile::BuckShot;
  data[Weapon::Shotgun].ammoCount = 25;
  data[Weapon::Shotgun].hitboxDimensions = sf::Vector2u(10,25);

  data[Weapon::Rifle].power = 2;
  data[Weapon::Rifle].range = 3;
  data[Weapon::Rifle].idleAnimationID = Animations::Rifle;
  data[Weapon::Rifle].moveAnimationID = Animations::Rifle;
  data[Weapon::Rifle].primaryAttackAnimationID = Animations::Rifle;
  data[Weapon::Rifle].secondaryAttackAnimationID = Animations::Rifle;
  data[Weapon::Rifle].primaryAttackType = Attack::Shoot;
  data[Weapon::Rifle].secondaryAttackType = Attack::Standard;
  data[Weapon::Rifle].primaryAttackSpeed = 0.5;
  data[Weapon::Rifle].secondaryAttackSpeed = 0.5;
  data[Weapon::Rifle].ammoType = Projectile::Bullet;
  data[Weapon::Rifle].ammoCount = 25;
  data[Weapon::Rifle].hitboxDimensions = sf::Vector2u(10,30);

  data[Weapon::SMG].power = 1;
  data[Weapon::SMG].range = 2;
  data[Weapon::SMG].idleAnimationID = Animations::SMG;
  data[Weapon::SMG].moveAnimationID = Animations::SMG;
  data[Weapon::SMG].primaryAttackAnimationID = Animations::SMG;
  data[Weapon::SMG].secondaryAttackAnimationID = Animations::SMG;
  data[Weapon::SMG].primaryAttackType = Attack::Shoot;
  data[Weapon::SMG].secondaryAttackType = Attack::Standard;
  data[Weapon::SMG].primaryAttackSpeed = 0.10;
  data[Weapon::SMG].secondaryAttackSpeed = 0.5;
  data[Weapon::SMG].ammoType = Projectile::Bullet;
  data[Weapon::SMG].ammoCount = 100;
  data[Weapon::SMG].hitboxDimensions = sf::Vector2u(10,25);

  data[Weapon::RocketLauncher].power = 2;
  data[Weapon::RocketLauncher].range = 3;
  data[Weapon::RocketLauncher].idleAnimationID = Animations::RocketLauncher_Idle;
  data[Weapon::RocketLauncher].moveAnimationID = Animations::RocketLauncher_Idle;
  data[Weapon::RocketLauncher].primaryAttackAnimationID = Animations::RocketLauncher_Idle;
  data[Weapon::RocketLauncher].secondaryAttackAnimationID = Animations::RocketLauncher_Idle;
  data[Weapon::RocketLauncher].primaryAttackType = Attack::Shoot;
  data[Weapon::RocketLauncher].secondaryAttackType = Attack::Standard;
  data[Weapon::RocketLauncher].primaryAttackSpeed = 1.0;
  data[Weapon::RocketLauncher].secondaryAttackSpeed = 0.5;
  data[Weapon::RocketLauncher].ammoType = Projectile::Rocket;
  data[Weapon::RocketLauncher].ammoCount = 4;
  data[Weapon::RocketLauncher].hitboxDimensions = sf::Vector2u(10,10);

  data[Weapon::Dagger].power = 3;
  data[Weapon::Dagger].range = 10;
  data[Weapon::Dagger].idleAnimationID = Animations::Empty;
  data[Weapon::Dagger].moveAnimationID = Animations::Empty;
  data[Weapon::Dagger].primaryAttackAnimationID = Animations::Empty;
  data[Weapon::Dagger].secondaryAttackAnimationID = Animations::Empty;
  data[Weapon::Dagger].primaryAttackType = Attack::Standard;
  data[Weapon::Dagger].secondaryAttackType = Attack::Standard;
  data[Weapon::Dagger].primaryAttackSpeed = 0.5;
  data[Weapon::Dagger].secondaryAttackSpeed = 0.5;

  data[Weapon::ShortSword].power = 3;
  data[Weapon::ShortSword].range = 10;
  data[Weapon::ShortSword].idleAnimationID = Animations::Empty;
  data[Weapon::ShortSword].moveAnimationID = Animations::Empty;
  data[Weapon::ShortSword].primaryAttackAnimationID = Animations::Empty;
  data[Weapon::ShortSword].secondaryAttackAnimationID = Animations::Empty;
  data[Weapon::ShortSword].primaryAttackType = Attack::Standard;
  data[Weapon::ShortSword].secondaryAttackType = Attack::Standard;
  data[Weapon::ShortSword].primaryAttackSpeed = 0.5;
  data[Weapon::ShortSword].secondaryAttackSpeed = 0.5;

  data[Weapon::Sword].power = 4;
  data[Weapon::Sword].range = 4;
  data[Weapon::Sword].idleAnimationID = Animations::Empty;
  data[Weapon::Sword].moveAnimationID = Animations::Empty;
  data[Weapon::Sword].primaryAttackAnimationID = Animations::Empty;
  data[Weapon::Sword].secondaryAttackAnimationID = Animations::Empty;
  data[Weapon::Sword].primaryAttackType = Attack::Standard;
  data[Weapon::Sword].secondaryAttackType = Attack::Standard;
  data[Weapon::Sword].primaryAttackSpeed = 0.3;
  data[Weapon::Sword].secondaryAttackSpeed = 0.3;

  data[Weapon::LongSword].power = 4;
  data[Weapon::LongSword].range = 4;
  data[Weapon::LongSword].idleAnimationID = Animations::Empty;
  data[Weapon::LongSword].moveAnimationID = Animations::Empty;
  data[Weapon::LongSword].primaryAttackAnimationID = Animations::Empty;
  data[Weapon::LongSword].secondaryAttackAnimationID = Animations::Empty;
  data[Weapon::LongSword].primaryAttackType = Attack::Standard;
  data[Weapon::LongSword].secondaryAttackType = Attack::Standard;
  data[Weapon::LongSword].primaryAttackSpeed = 0.3;
  data[Weapon::LongSword].secondaryAttackSpeed = 0.3;

  data[Weapon::SingleAxe].power = 4;
  data[Weapon::SingleAxe].range = 5;
  data[Weapon::SingleAxe].idleAnimationID = Animations::Empty;
  data[Weapon::SingleAxe].moveAnimationID = Animations::Empty;
  data[Weapon::SingleAxe].primaryAttackAnimationID = Animations::Empty;
  data[Weapon::SingleAxe].secondaryAttackAnimationID = Animations::Empty;
  data[Weapon::SingleAxe].primaryAttackType = Attack::Standard;
  data[Weapon::SingleAxe].secondaryAttackType = Attack::Standard;
  data[Weapon::SingleAxe].primaryAttackSpeed = 0.4;
  data[Weapon::SingleAxe].secondaryAttackSpeed = 0.4;

  data[Weapon::DoubleAxe].power = 4;
  data[Weapon::DoubleAxe].range = 5;
  data[Weapon::DoubleAxe].idleAnimationID = Animations::Empty;
  data[Weapon::DoubleAxe].moveAnimationID = Animations::Empty;
  data[Weapon::DoubleAxe].primaryAttackAnimationID = Animations::Empty;
  data[Weapon::DoubleAxe].secondaryAttackAnimationID = Animations::Empty;
  data[Weapon::DoubleAxe].primaryAttackType = Attack::Standard;
  data[Weapon::DoubleAxe].secondaryAttackType = Attack::Standard;
  data[Weapon::DoubleAxe].primaryAttackSpeed = 0.4;
  data[Weapon::DoubleAxe].secondaryAttackSpeed = 0.4;

  data[Weapon::Spear].power = 4;
  data[Weapon::Spear].range = 5;
  data[Weapon::Spear].idleAnimationID = Animations::Empty;
  data[Weapon::Spear].moveAnimationID = Animations::Empty;
  data[Weapon::Spear].primaryAttackAnimationID = Animations::Empty;
  data[Weapon::Spear].secondaryAttackAnimationID = Animations::Empty;
  data[Weapon::Spear].primaryAttackType = Attack::Standard;
  data[Weapon::Spear].secondaryAttackType = Attack::Standard;
  data[Weapon::Spear].primaryAttackSpeed = 0.4;
  data[Weapon::Spear].secondaryAttackSpeed = 0.4;

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

  data[Collidable::Boundary].hitpoints = 10000000;
  data[Collidable::Boundary].speed = 0;
  data[Collidable::Boundary].power = 0;
  data[Collidable::Boundary].idleAnimationID = Animations::Empty;
  data[Collidable::Boundary].color = sf::Color::White;

  data[Collidable::SheepPen].hitpoints = 10000000;
  data[Collidable::SheepPen].speed = 0;
  data[Collidable::SheepPen].power = 0;
  data[Collidable::SheepPen].idleAnimationID = Animations::Empty;
  data[Collidable::SheepPen].color = sf::Color::Blue;

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
