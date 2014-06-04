
#include "level.h"

Level::Level()
  : map("map2.txt"),
    textures()
{
  textures.Load(Textures::Hero, "character-sprite-map.gif");
  textures.Load(Textures::SpriteSheet, "spritesheet.png");

  hero.CreateSprite(textures);
  hero.CreateAnimatedSprite();
  hero.CreateAnimations(textures);

  npc.push_back(CreateNPC(NPC::Goomba));
  npc.push_back(CreateNPC(NPC::Chumba));
};

NPC* Level::CreateNPC(NPC::Type type)
{
  NPC* p_enemy;
  p_enemy = new NPC(type);
  p_enemy->CreateSprite(this->textures);
  return p_enemy;
}
