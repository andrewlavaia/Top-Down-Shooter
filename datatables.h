
#ifndef DATATABLES_H
#define DATATABLES_H

#include "resourceholder.h"
#include "direction.h"
#include "hero.h"
#include "weapon.h"
#include "npc.h"
#include "collidable.h"
#include "projectile.h"

struct HeroData
{
    double          hitpoints = 50;
    double          speed = 1;
    double          power = 1;
    Animations::ID  idleAnimationID = Animations::Empty;
    Animations::ID  moveAnimationID = Animations::Empty;
    Animations::ID  dieAnimationID = Animations::Empty;
    Animations::ID  deadAnimationID = Animations::Empty;
    Animations::ID  attackedAnimationID = Animations::Empty;
    Animations::ID  grabAnimationID = Animations::Empty;
    Animations::ID  punchAnimationID = Animations::Empty;
    sf::Color       color = sf::Color::White; // default represents no color
    sf::Vector2u    hitboxDimensions = sf::Vector2u(20,20);
    double          scaleFactor = 2.0;
};

struct NPCData
{
    double          hitpoints = 10;
    double          speed = 1;
    double          power = 1;
    Animations::ID  idleAnimationID = Animations::Empty;
    Animations::ID  moveAnimationID = Animations::Empty;
    Animations::ID  dieAnimationID = Animations::Empty;
    Animations::ID  deadAnimationID = Animations::Empty;
    Animations::ID  attackedAnimationID = Animations::Empty;
    Animations::ID  grabbedAnimationID = Animations::Empty;
    Animations::ID  thrownAnimationID = Animations::Empty;
    sf::Color       color = sf::Color::White; //default represents no color
    sf::Vector2u    hitboxDimensions = sf::Vector2u(20,20);
    Weapon::Type    weapon = Weapon::Hands;
    double          scaleFactor = 2.0;
};

struct WeaponData
{
    double          hitpoints = 10.0; // durability
    double          speed = 0.0; // movement speed
    double          power = 1.0; // melee attack power only, projectiled have their own power
    unsigned        range = 1; // melee range only, projectiles fired have their own range

    Attack::Type    primaryAttackType = Attack::Standard;
    Attack::Type    secondaryAttackType = Attack::Standard;
    double          primaryAttackSpeed = 0.5;
    double          secondaryAttackSpeed = 0.5;

    Projectile::Type ammoType = Projectile::Empty;
    unsigned         ammoCount = 0;

    Animations::ID  idleAnimationID = Animations::Empty;
    Animations::ID  moveAnimationID = Animations::Empty;
    Animations::ID  dieAnimationID = Animations::Empty;
    Animations::ID  primaryAttackAnimationID = Animations::Empty;
    Animations::ID  secondaryAttackAnimationID = Animations::Empty;
    sf::Color       color = sf::Color::White; //default represents no color
    sf::Vector2u    hitboxDimensions = sf::Vector2u(10, 10);
    sf::Vector2u    originDimensions = sf::Vector2u(0, 0);
    double          scaleFactor = 1.0;
};

struct CollidableData
{
    double          hitpoints = 10000000; // indestructible
    double          speed = 0;
    double          power = 0;
    Animations::ID  idleAnimationID = Animations::Empty;
    sf::Color       color = sf::Color::White; //default represents no color
};

struct ProjectileData
{
    double          hitpoints = 1.0;
    double          speed = 20.0;
    double          power = 1.0;
    unsigned        range = 500;
    Animations::ID  moveAnimationID = Animations::Empty;
    Animations::ID  dieAnimationID = Animations::Empty;
    sf::Color       color = sf::Color::White; //default represents no color
    sf::Vector2u    hitboxDimensions = sf::Vector2u(5,5);
    double          scaleFactor = 1.0;
};

class DataTable
{
public:
  DataTable();

  const std::vector<HeroData>       HeroTable;
  const std::vector<NPCData>        NPCTable;
  const std::vector<WeaponData>     WeaponTable;
  const std::vector<CollidableData> CollidableTable;
  const std::vector<ProjectileData> ProjectileTable;

private:
  std::vector<HeroData>       initializeHeroData();
  std::vector<NPCData>        initializeNPCData();
  std::vector<WeaponData>     initializeWeaponData();
  std::vector<CollidableData> initializeCollidableData();
  std::vector<ProjectileData> initializeProjectileData();

};
#endif // DATATABLES_H include
