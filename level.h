#ifndef LEVEL_H
#define LEVEL

#include <vector>
#include <memory>
#include "mapmanager.h"
#include "texturemanager.h"
#include "hero.h"
#include "npc.h"

class Level
{
public:
                                          Level();

  void                                    Load(int id);
  void                                    CreateNPC(NPC::Type type);
  void                                    CreateWeapon(Weapon::Type type);
  void                                    MoveNPCs();


  MapManager                              mp;
  TextureManager                          textures;
  Hero                                    hero;
  std::vector< std::unique_ptr<NPC> >     npc;
  std::vector< std::unique_ptr<Weapon> >  weapon;

private:
  Level(const Level&);              // Disallow copy constructor
  Level& operator=(const Level&);   // Disallow assignment

};

#endif // LEVEL_H
