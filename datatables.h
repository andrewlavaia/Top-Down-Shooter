
#ifndef DATATABLES_H
#define DATATABLES_H

#include "resourceholder.h"
#include "direction.h"
#include "hero.h"
#include "npc.h"
#include "weapon.h"
#include "collidable.h"
#include "projectile.h"


struct HeroData
{
    double          hitpoints;
    double          speed;
    double          power;
    Animations::ID  idleAnimationID;
    Animations::ID  moveAnimationID;
    Animations::ID  dieAnimationID;
    Animations::ID  deadAnimationID;
    Animations::ID  attackedAnimationID;
    Animations::ID  punchAnimationID;
    Animations::ID  kickAnimationID;
    sf::Color       color = sf::Color::White; //default represents no color
    sf::Vector2u    origin;
    sf::Vector2u    hitboxDimensions;
};

struct NPCData
{
    double          hitpoints;
    double          speed;
    double          power;
    Animations::ID  idleAnimationID;
    Animations::ID  moveAnimationID;
    Animations::ID  dieAnimationID;
    Animations::ID  deadAnimationID;
    Animations::ID  attackedAnimationID;
    Animations::ID  grabbedAnimationID;
    Animations::ID  thrownAnimationID;
    sf::Color       color = sf::Color::White; //default represents no color
    sf::Vector2u    origin;
    sf::Vector2u    hitboxDimensions;
    //std::vector<Direction> defaultAI;
};

struct WeaponData
{
    double          hitpoints;
    double          speed;
    double          power;
    int             range;
    Attack::Type    primaryAttackType;
    Attack::Type    secondaryAttackType;
    double          primaryAttackSpeed;
    double          secondaryAttackSpeed;
    Projectile::Type ammoType;
    unsigned        ammoAmount; // starting ammo, no way of increasing ammo at this point
    Animations::ID  idleAnimationID;
    Animations::ID  moveAnimationID;
    Animations::ID  primaryAnimationID;
    Animations::ID  secondaryAnimationID;
    sf::Color       color = sf::Color::White; //default represents no color
    sf::Vector2u    origin;
    sf::Vector2u    hitboxDimensions;
};

struct CollidableData
{
    double          hitpoints = 0;
    double          speed = 0;
    double          power = 0;
    Animations::ID  idleAnimationID;
    sf::Color       color = sf::Color::White; //default represents no color
    sf::Vector2u    origin;
    sf::Vector2u    hitboxDimensions;
};

struct ProjectileData
{
    double          hitpoints;
    double          speed;
    double          power;
    Animations::ID  idleAnimationID;
    Animations::ID  moveAnimationID;
    Animations::ID  dieAnimationID;
    Animations::ID  deadAnimationID;
    sf::Color       animatedSpriteColor = sf::Color::White; //default represents no color
    sf::Vector2u    origin;
    sf::Vector2u    hitboxDimensions;
};

class DataTable
{
public:
  DataTable();

  const std::vector<NPCData>        NPCTable;
  const std::vector<WeaponData>     WeaponTable;
  const std::vector<CollidableData> CollidableTable;
  const std::vector<ProjectileData> ProjectileTable;


private:
  std::vector<NPCData>        initializeNPCData();
  std::vector<WeaponData>     initializeWeaponData();
  std::vector<CollidableData> initializeCollidableData();
  std::vector<ProjectileData> initializeProjectileData();

};
#endif // DATATABLES_H include
