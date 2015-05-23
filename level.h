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
#include "npc.h"
#include "weapon.h"
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
  unsigned                                    getNPCDeathCount() const { return npc_death_count; };
  const sf::Vector2f                          getBounds() const { return bounds; }

  MapManager                                   mp;
  std::vector<std::shared_ptr<AnimatedEntity>> entities;
  std::vector<std::shared_ptr<AnimatedEntity>> exits;


private:
  Level(const Level&);                        // Disallow copy constructor
  Level& operator=(const Level&);             // Disallow assignment

  template <typename T1, typename T2>
    void DestroyObject(T1& vec, T2& it);

  void                                        CreateNPC(NPC::Type type, double x, double y);
  void                                        CreateWeapon(Weapon::Type type, double x, double y);
  void                                        CreateProjectile(Projectile::Type type, double x, double y, Orientation::Type o);
  void                                        CreateCollidable(Collidable::Type type, int x, int y, int width, int height);

  int                                         level_id;
  const ResourceHolder<Animation, Animations::ID>&  animations;
  const DataTable&                            data;
  const sf::Vector2f                          bounds; // width, height of playable area in level
  sf::Clock                                   running_time;
  sf::Time                                    gameover_time;
  unsigned                                    npc_death_count;






};


#endif // LEVEL_H
