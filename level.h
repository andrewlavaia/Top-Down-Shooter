#ifndef LEVEL_H
#define LEVEL

#include <vector>
#include <memory>
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



class Level
{
public:

  Level(int id, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data);


  void                                        MoveEntities();
  void                                        DeleteEntities();


  float                                       getRunningTime();
  float                                       getGameOverTime();
  unsigned                                    getEnemyDeathCount() const { return enemy_death_count; };
  const sf::Vector2f                          getBounds() const { return bounds; }
  void                                        CreateNPC(NPC::Type type, double x, double y);

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

  // createProjectile should be reworked so that it can be used for npc and hero weapons and so animations and data can go back to being private
  //void                                        CreateProjectile(Projectile::Type type, double x, double y, Orientation::Type o);
  void                                        CreateWeapon(Weapon::Type type, double x, double y);
  void                                        CreateCollidable(Collidable::Type type, int x, int y, int width, int height);

  int                                         level_id;


  const sf::Vector2f                          bounds; // width, height of playable area in level
  sf::Clock                                   running_time;
  sf::Time                                    gameover_time;
  unsigned                                    enemy_death_count;
  unsigned                                    sheep_pen_count;
  unsigned                                    sheep_total;


};


#endif // LEVEL_H
