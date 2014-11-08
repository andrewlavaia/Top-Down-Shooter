#ifndef LEVEL_H
#define LEVEL

#include <vector>
#include <memory>
#include "mapmanager.h"
#include "texturemanager.h"
#include "hero.h"
#include "npc.h"
#include "collidable.h"

class Level
{
public:
                                              Level();

  void                                        Load(int id);
  void                                        CreateNPC(NPC::Type type);
  void                                        CreateWeapon(Weapon::Type type);
  void                                        CreateCollidable(Collidable::Type type, double x, double y, double width, double height);
  void                                        MoveNPCs();
  void                                        MoveWeapons();
  void                                        DestroyNPC(std::vector<std::unique_ptr<NPC>>::iterator it);
  void                                        CheckCollision_NPCtoHero(std::vector<std::unique_ptr<NPC>>::iterator it);
  void                                        CheckCollision_NPCtoNPC(std::vector<std::unique_ptr<NPC>>::iterator it);
  void                                        CheckCollision_NPCtoCollidable(std::vector<std::unique_ptr<NPC>>::iterator it);
  bool                                        Victory();
  float                                       getRunningTime();
  float                                       getGameOverTime();

  // HUD Elements
  sf::Text                                    text_timer;


  MapManager                                  mp;
  TextureManager                              textures;

  Hero                                        hero;
  std::vector< std::unique_ptr<NPC> >         npc;
  //std::vector< std::unique_ptr<Weapon> >      weapon;
  std::vector< std::unique_ptr<Collidable> >  collidables;

  std::vector< std::shared_ptr<Weapon> >      weapons;



private:
  Level(const Level&);                        // Disallow copy constructor
  Level& operator=(const Level&);             // Disallow assignment

  template <typename T>
    void MoveObject(T& it);

  unsigned                                     victory_requirement;
  unsigned                                     npc_success_count;
  unsigned                                     npc_death_count;
  sf::Time                                     gameover_time;
  sf::Clock                                    running_time;

  sf::Font                                     font_HUD;

};

#endif // LEVEL_H
