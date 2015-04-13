#ifndef LEVEL_H
#define LEVEL

#include <vector>
#include <memory>
#include "mapmanager.h"
#include "resourceholder.h"
#include "animatedentity.h"
#include "hero.h"
#include "npc.h"
#include "collidable.h"
#include "projectile.h"
#include "orientation.h"
#include "animation.h"

class Level
{
public:

  Level(int id, std::shared_ptr<Hero> h);

  void                                        Load(int id);
  void                                        CreateNPC(NPC::Type type);
  void                                        CreateWeapon(Weapon::Type type, double x, double y);
  void                                        CreateProjectile(Projectile::Type type, double x, double y, Orientation::Type o);
  void                                        CreateCollidable(Collidable::Type type, int x, int y, int width, int height);
  void                                        MoveEntities();
  void                                        DeleteEntities();

  bool                                        Victory();
  bool                                        GameOver();

  float                                       getRunningTime();
  float                                       getGameOverTime();
  unsigned                                    getNPCSuccessCount() const { return npc_success_count; };

  // HUD Elements
  sf::Text                                    text_timer;
  sf::Text                                    text_npc_count;

  MapManager                                  mp;

  std::vector<std::shared_ptr<AnimatedEntity>> entities;
  std::vector<std::shared_ptr<AnimatedEntity>> exits;


private:
  Level(const Level&);                        // Disallow copy constructor
  Level& operator=(const Level&);             // Disallow assignment

  template <typename T1, typename T2>
    void DestroyObject(T1& vec, T2& it);

  int                                         level_id;
  std::shared_ptr<Hero>                       hero;                 // needs a copy of pointer for collision tests
  unsigned                                    victory_requirement;
  unsigned                                    npc_success_count;
  unsigned                                    npc_death_count;
  sf::Time                                    gameover_time;
  sf::Clock                                   running_time;
  ResourceHolder<sf::Texture, Textures::ID>   textures;
  ResourceHolder<sf::Font, Fonts::ID>         fonts;
  ResourceHolder<Animation, Animations::ID>   animations;
  bool                                        next_level_flag;
  bool                                        next_room_flag;

};


#endif // LEVEL_H
