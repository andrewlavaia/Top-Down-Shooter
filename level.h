#ifndef LEVEL_H
#define LEVEL

#include <vector>
#include "mapmanager.h"
#include "hero.h"
#include "npc.h"


class Level
{
public:
  Level();

  MapManager map;
  Hero hero;
  NPC npc0;
  NPC npc1;
  std::vector<NPC> npc{npc0,npc1};

};

#endif // LEVEL_H
