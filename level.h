#ifndef LEVEL_H
#define LEVEL

#include <vector>
#include "mapmanager.h"
#include "texturemanager.h"
#include "hero.h"
#include "npc.h"

class Level
{
public:
  Level();

  NPC* CreateNPC(NPC::Type type);

  MapManager map;
  TextureManager textures;
  Hero hero;
  std::vector<NPC*> npc;

private:
  Level(const Level&);              // Disallow copy constructor
  Level& operator=(const Level&);   // Disallow assignment

};

#endif // LEVEL_H
