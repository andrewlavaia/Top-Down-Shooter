#ifndef LEVEL_H
#define LEVEL

#include <vector>
#include <memory>
#include <random>
#include <chrono>

#include "mapmanager.h"
#include "resourceholder.h"
#include "animation.h"
#include "animatedentity.h"
#include "orientation.h"

#include "datatables.h"
#include "weapon.h"
#include "npc.h"
#include "collidable.h"
#include "projectile.h"
#include <cassert>


class Level
{
public:

  Level(int id, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data);


  void                                        MoveEntities();
  void                                        DeleteEntities();

  unsigned                                    getEnemyDeathCount() const { return enemy_death_count; };
  const sf::Vector2f                          getBounds() const { return bounds; }
  void                                        CreateNPC(NPC::Type type, sf::Vector2f coord);
  void                                        CreateRandomNPC(sf::Vector2f location);
  sf::Vector2f                                getRandomNearbyLocation(sf::Vector2f location);

  void                                        spawnNPCs(unsigned n, sf::Time dt, sf::Vector2f location);

  MapManager                                   mp;
  sf::Sprite                                   background;
  std::vector<std::shared_ptr<AnimatedEntity>> entities;

  const ResourceHolder<Animation, Animations::ID>&  animations;
  const DataTable&                            data;

private:
  Level(const Level&);                        // Disallow copy constructor
  Level& operator=(const Level&);             // Disallow assignment

  template <typename T1, typename T2>
    void DestroyObject(T1& vec, T2& it);

  void                                        CreateWeapon(Weapon::Type type, sf::Vector2f location);
  void                                        CreateCollidable(Collidable::Type type, int x, int y, int width, int height);
  bool                                        canSpawn();
  void                                        reduceSpawnCooldown(sf::Time dt);
  void                                        resetSpawnCooldown();

  NPC::Type                                   getRandomNPCType();
  Weapon::Type                                getRandomWeaponType();

  int                                         level_id;

  const sf::Vector2f                          bounds; // width, height of playable area in level
  unsigned                                    enemy_death_count;
  unsigned                                    sheep_pen_count;
  unsigned                                    sheep_total;

  sf::Time                                    spawn_cooldown;
  unsigned                                    spawn_count;



};


#endif // LEVEL_H
