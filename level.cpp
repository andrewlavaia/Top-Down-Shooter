
#include "level.h"

Level::Level()
{

}

void Level::Load(int id)
{

  // Delete all existing NPCs and deallocate memory
  npc.clear(); // std::unique_ptr will delete pointed to object automatically

  // Load Level
  switch (id)
  {
    case 1:
      mp.Load("map2.txt");
      textures.Load(Textures::Hero, "spritesheet.png");
      textures.Load(Textures::NPC, "character-sprite-map.gif");

      hero.CreateAnimatedSprite();
      hero.CreateAnimations(textures);

      CreateNPC(NPC::Goomba);
      CreateNPC(NPC::Chumba);

      weapon.push_back(CreateWeapon(Weapon::Lasso));
      weapon.push_back(CreateWeapon(Weapon::Pole));
      weapon.push_back(CreateWeapon(Weapon::Pole));
      weapon.push_back(CreateWeapon(Weapon::Lasso));

      break;

    case 2:
      mp.Load("map_L2.txt");
      textures.Load(Textures::Hero, "spritesheet.png");

      hero.CreateAnimatedSprite();
      hero.CreateAnimations(textures);

      CreateNPC(NPC::Goomba);
      CreateNPC(NPC::Chumba);

      break;

    default:
      std::cout << "Level failed to load... loading Level 1";
      Level::Load(1);
      break;
  }
}

// Dynamically creates a new NPC object and returns a smart pointer to it
void Level::CreateNPC(NPC::Type type)
{
  std::unique_ptr<NPC> p_enemy( new NPC(type) );
  p_enemy->CreateAnimatedSprite();
  p_enemy->CreateAnimations(this->textures);
  npc.push_back( std::move(p_enemy) );
}

// Dynamically creates a new Weapon object and returns a smart pointer to it
std::unique_ptr<Weapon> Level::CreateWeapon(Weapon::Type type)
{
  std::unique_ptr<Weapon> p_weapon( new Weapon(type) );
  return p_weapon;
}



/// DEPRECATED - not needed with smart pointer implementation
/*
// Iterates through the vector of NPC pointers, deallocates the memory, and then clears the container
void Level::DeleteAllNPCs()
{
    for (std::vector<NPC*>::const_iterator it = npc.begin(); it !=npc.end(); it++)
    {
      delete *it;
    }
    npc.clear(); //necessary, otherwise leaves a vector of dead pointers
}
*/
