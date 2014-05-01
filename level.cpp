
  #include "level.h"

  Level::Level()
    : map("map2.txt"),
      textures()
  {
    textures.Load(Textures::Hero, "character-sprite-map.gif");

    hero.CreateSprite(textures);

    NPC enemy1(NPC::Goomba);
    enemy1.CreateSprite(textures);
    npc.push_back(enemy1);

    NPC enemy2(NPC::Chumba);
    enemy2.CreateSprite(textures);
    npc.push_back(enemy2);

  };
