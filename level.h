#ifndef LEVEL_H
#define LEVEL


#include "mapmanager.h"
#include "hero.h"
#include "npc.h"

class Level
{
public:
  Level () : map("map2.txt") {};

  MapManager map;
  Hero hero;
  NPC npc;

};

#endif // LEVEL_H
