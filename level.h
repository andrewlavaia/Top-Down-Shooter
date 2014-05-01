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

  MapManager map;
  TextureManager textures;
  Hero hero;
  std::vector<NPC> npc;

};

#endif // LEVEL_H
