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


  MapManager                                  mp;
  TextureManager                              textures;

  Hero                                        hero;
  std::vector< std::unique_ptr<NPC> >         npc;
  std::vector< std::unique_ptr<Weapon> >      weapon;
  std::vector< std::unique_ptr<Collidable> >  collidables;

private:
  Level(const Level&);              // Disallow copy constructor
  Level& operator=(const Level&);   // Disallow assignment

  template <typename T>
    void MoveObject(T& it);

};

#endif // LEVEL_H
