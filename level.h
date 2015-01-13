#ifndef LEVEL_H
#define LEVEL

#include <vector>
#include <memory>
#include "mapmanager.h"
#include "texturemanager.h"
#include "animatedentity.h"
#include "hero.h"
#include "npc.h"
#include "collidable.h"
#include "projectile.h"
#include "orientation.h"

class Level
{
public:
                                              Level();

  void                                        Load(int id);
  void                                        CreateNPC(NPC::Type type);
  void                                        CreateWeapon(Weapon::Type type);
  void                                        CreateProjectile(Projectile::Type type, double x, double y, Orientation::Type o);
  void                                        CreateCollidable(Collidable::Type type, int x, int y, int width, int height);
  void                                        MoveEntities();
  //void                                        MoveNPCs();
  //void                                        MoveWeapons();
  //void                                        MoveProjectiles();
  //void                                        DestroyNPC(std::vector<std::shared_ptr<NPC>>::iterator it);
  //void                                        CheckCollision_NPCtoHero(std::vector<std::shared_ptr<NPC>>::iterator it);
  //void                                        CheckCollision_NPCtoNPC(std::vector<std::shared_ptr<NPC>>::iterator it);
  //void                                        CheckCollision_NPCtoCollidable(std::vector<std::shared_ptr<NPC>>::iterator it);
  void                                        DeleteEntities();
  bool                                        Victory();
  bool                                        GameOver();
  float                                       getRunningTime();
  float                                       getGameOverTime();
  unsigned                                    getNPCSuccessCount() { return npc_success_count; };

  // HUD Elements
  sf::Text                                    text_timer;
  sf::Text                                    text_npc_count;

  MapManager                                  mp;
  TextureManager                              textures;

  Hero                                        hero;
  //std::vector< std::shared_ptr<Collidable> >  collidables;
  //std::vector< std::shared_ptr<NPC> >         npc;
  //std::vector< std::shared_ptr<Weapon> >      weapons;
  //std::vector< std::shared_ptr<Projectile> >  projectiles;
  std::vector< std::shared_ptr<AnimatedEntity> > entities;

private:
  Level(const Level&);                        // Disallow copy constructor
  Level& operator=(const Level&);             // Disallow assignment

  template <typename T1, typename T2>
    void DestroyObject(T1& vec, T2& it);

  unsigned                                     victory_requirement;
  unsigned                                     npc_success_count;
  unsigned                                     npc_death_count;
  sf::Time                                     gameover_time;
  sf::Clock                                    running_time;

  sf::Font                                     font_HUD;

};

#endif // LEVEL_H
