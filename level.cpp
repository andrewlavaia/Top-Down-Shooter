
#include "level.h"

Level::Level()
{

}

// need to add destructor that removes all npcs created

void Level::Load(int id)
{
  switch (id)
  {
    case 1:
      mp.Load("map2.txt");
      textures.Load(Textures::Hero, "spritesheet.png");
      textures.Load(Textures::NPC, "character-sprite-map.gif");

      hero.CreateAnimatedSprite();
      hero.CreateAnimations(textures);

      npc.push_back(CreateNPC(NPC::Goomba));
      npc.push_back(CreateNPC(NPC::Chumba));

      break;

    case 2:
      mp.Load("map_L2.txt");
      textures.Load(Textures::Hero, "spritesheet.png");

      hero.CreateAnimatedSprite();
      hero.CreateAnimations(textures);

      npc.push_back(CreateNPC(NPC::Goomba));
      npc.push_back(CreateNPC(NPC::Chumba));

      break;

    default:
      std::cout << "Level failed to load... loading Level 1";
      Level::Load(1);
      break;
  }
}

NPC* Level::CreateNPC(NPC::Type type)
{
  NPC* p_enemy;
  p_enemy = new NPC(type);
  p_enemy->CreateAnimatedSprite();
  p_enemy->CreateAnimations(this->textures);
  return p_enemy;
}
