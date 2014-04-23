#ifndef LEVEL_H
#define LEVEL


#include "mapmanager.h"
#include "hero.h"

class Level
{
public:
  Level () : map("map2.txt") {};

  MapManager map;
  Hero hero;

};

#endif // LEVEL_H
