
#include "level.h"
#include <math.h> // sqrt

Level::Level()
  : victory_requirement(5),
    npc_success_count(0),
    gameover_time(sf::seconds(30.0f))
{
  textures.Load(Textures::Hero_Run, "hero_run.png");
  textures.Load(Textures::Hero_Grab, "hero_grab.png");
  textures.Load(Textures::Hero_Punch, "hero_punch.png");
  textures.Load(Textures::Hero_Kick, "hero_kick.png");
  textures.Load(Textures::NPC_Texture, "spritesheet.png");

  if(!font_HUD.loadFromFile("calibri.ttf"))
  {
    //throw exception...
    std::cout<<"Font Not Loaded"<<std::endl;
  }
  text_timer.setFont(font_HUD);
  text_timer.setCharacterSize(40);
  text_timer.setColor(sf::Color::Black);
  text_timer.setPosition(400,20);

  text_npc_count.setFont(font_HUD);
  text_npc_count.setCharacterSize(40);
  text_npc_count.setColor(sf::Color::Black);
  text_npc_count.setPosition(700,20);
}

void Level::Load(int id)
{
  running_time.restart();

  // clear vectors and deallocate memory

/*
  npc.clear(); // std::unique_ptr will delete object automatically, deleting any existing NPCs
  weapons.clear();
  collidables.clear();
*/

  // Load Level
  switch (id)
  {
    case 1:
      mp.Load("map2.txt");
                                                   //  x     y   width  height
      CreateCollidable(Collidable::SubwayDoor,          0,   300,  30,   200);
      CreateCollidable(Collidable::SubwayRail,          0,     0,  30,   268);
      CreateCollidable(Collidable::SubwayRail,          0,   500,  30,   300);
      CreateCollidable(Collidable::ImmovableObject,     0,   269,  30,    30);
      CreateCollidable(Collidable::ImmovableObject,     0,   469,  30,    30);
      CreateCollidable(Collidable::SubwayPlatform,      30,    0,  50,   800);
      CreateCollidable(Collidable::ImmovableObject,     500, 500, 100,    10);

      hero.CreateAnimations(textures);

      CreateNPC(NPC::Goomba);
      CreateNPC(NPC::Chumba);

      CreateWeapon(Weapon::Lasso);
      CreateWeapon(Weapon::Pole);
      CreateWeapon(Weapon::Pole);
      CreateWeapon(Weapon::Lasso);

      break;

    case 2:
      mp.Load("map_L2.txt");

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
  std::shared_ptr<NPC> p_npc( new NPC(type, textures) );
  entities.push_back(p_npc);
}

// Dynamically creates a new Weapon object and returns a smart pointer to it
void Level::CreateWeapon(Weapon::Type type)
{
 // std::unique_ptr<Weapon> p_weapon( new Weapon(type) );
 // weapon.push_back( std::move(p_weapon) );

  std::shared_ptr<Weapon> w(new Weapon(type));
  entities.push_back(w);
}

void Level::CreateProjectile(Projectile::Type type, double x, double y, Orientation::Type o)
{
  std::shared_ptr<Projectile> p(new Projectile(type, x, y, o));
  entities.push_back(p);
}

// Dynamically creates a new Collidable object and returns a smart pointer to it
void Level::CreateCollidable(Collidable::Type type, int x, int y, int width, int height)
{
  std::shared_ptr<Collidable> p(new Collidable(type, x, y, width, height));
  entities.push_back(p);
}
void Level::MoveEntities()
{
  if(hero.grabbed_npc != nullptr)
  {
    hero.grabbed_npc->position.x = hero.position.x;
    hero.grabbed_npc->position.y = hero.position.y - 30;
    // set currentAnimation to "grabbed"
  }
  if (hero.weapon != nullptr)
  {
    hero.weapon->position = hero.position;
  }

  for (std::vector< std::shared_ptr<AnimatedEntity> >::iterator it = entities.begin(); it != entities.end();)
  {
    (*it)->Move();

    if(typeid(**it) == typeid(Projectile) && (*it)->directions.empty())
      DestroyObject(entities, it);
    else
      ++it;
  }

}

void Level::DeleteEntities()
{
  for (std::vector< std::shared_ptr<AnimatedEntity> >::iterator it = entities.begin(); it != entities.end(); )
  {
    if((*it)->getDestroyFlag() == true)
      DestroyObject(entities, it);
    else
      ++it;
  }

}

/*
void Level::MoveNPCs()
{
  if(hero.grabbed_npc != nullptr)
  {
    hero.grabbed_npc->position.x = hero.position.x;
    hero.grabbed_npc->position.y = hero.position.y - 30;
    // set currentAnimation to "grabbed"
  }


  for (std::vector< std::shared_ptr<NPC> >::iterator it = npc.begin(); it != npc.end(); ++it)
  {
      (*it)->Move();
  }

}

void Level::MoveWeapons()
{
  if (hero.weapon != nullptr)
  {
    hero.weapon->position = hero.position;
  }

  for (std::vector< std::shared_ptr<Weapon> >::iterator it = weapons.begin(); it != weapons.end(); ++it)
  {
    (*it)->Move();
  }
}

void Level::MoveProjectiles()
{
  for (std::vector< std::shared_ptr<Projectile> >::iterator it = projectiles.begin(); it != projectiles.end(); )
  {
    (*it)->Move();

    if((*it)->directions.empty() == true)
    {
      DestroyObject(projectiles, it);
    }
    else
    {
      ++it;
    }
  }
}

void Level::DestroyNPC(std::vector<std::shared_ptr<NPC>>::iterator it)
{
  // erase remove idiom
  DestroyObject(npc, it);
}

*/

template <typename T1, typename T2>
void Level::DestroyObject(T1& vec, T2& it)
{
  // erase remove idiom
  vec.erase(std::remove(vec.begin(), vec.end(), *it),
            vec.end());

}

/*

// Check if NPC has collided with the hero
void Level::CheckCollision_NPCtoHero(std::vector<std::shared_ptr<NPC>>::iterator it)
{
  // if hero hits any npc, npc bumped back (based on hero strength and npc weight)
  if(Collision::BoundingBoxTest(hero.animatedSprite.hitbox, (*it)->animatedSprite.hitbox))
  {
    //(*it)->position.x += (hero.position.x - (*it)->position.x) * 10;
    //(*it)->position.y += (hero.position.y - (*it)->position.y) * 10;
    //(*it)->position += hero.position - (*it)->position; // allows player to stick to npcs by touching them
    //(*it)->Move(hero.getOrientation().getOppo(),hero.strength/(*it)->getWeight(),15);
    (*it)->position.x += (hero.strength/(*it)->getWeight()) * ((*it)->position.x - hero.position.x)/4;
    (*it)->position.y += (hero.strength/(*it)->getWeight()) * ((*it)->position.y - hero.position.y)/4;
  }
}

// Check if NPC has collided with any of the level's other NPCs
void Level::CheckCollision_NPCtoNPC(std::vector<std::shared_ptr<NPC>>::iterator it)
{

  // if any npc runs into another npc, they each are bumped back (based on their weight)
  for (std::vector< std::shared_ptr<NPC> >::iterator jt = npc.begin(); jt != npc.end(); ++jt)
  {
    if( it != jt && Collision::BoundingBoxTest( (*jt)->animatedSprite.hitbox, (*it)->animatedSprite.hitbox))
    {
      // check which npc has more force (mass * speed)
      double i_force = (*it)->directions_it->getSpeed() * (*it)->getWeight();
      double j_force = (*jt)->directions_it->getSpeed() * (*jt)->getWeight();

      // initialize variables first so that each npc moves back the same distance
      double ix = (*it)->position.x;
      double iy = (*it)->position.y;
      double jx = (*jt)->position.x;
      double jy = (*jt)->position.y;

      if(i_force > j_force) // npc *jt will be pushed back
      {
        //(*jt)->Move((*it)->directions_it->getType(),5,20);
        (*jt)->position.x += (1/(*jt)->getWeight()) * (jx - ix)/4;
        (*jt)->position.y += (1/(*jt)->getWeight()) * (jy - iy)/4;
      }
      else if(i_force < j_force) // npc *it will be pushed back
      {
        //(*it)->Move((*jt)->directions_it->getType(),5,20);
        //(*it)->MoveOppo(10);
        (*it)->position.x += (1/(*it)->getWeight()) * (ix - jx)/4;
        (*it)->position.y += (1/(*it)->getWeight()) * (iy - jy)/4;
      }
      else if(i_force == j_force) // both pushed back
      {
        //(*jt)->Move((*it)->directions_it->getType(),5,20);
        //(*it)->Move((*jt)->directions_it->getType(),5,10); //different distance so no infinite collision if in same direction
        //(*jt)->MoveOppo(10);
        //(*it)->MoveOppo(10);

        (*jt)->position.x += (1/(*jt)->getWeight()) * (jx - ix)/8;
        (*jt)->position.y += (1/(*jt)->getWeight()) * (jy - iy)/8;
        (*it)->position.x += (1/(*it)->getWeight()) * (ix - jx)/8;
        (*it)->position.y += (1/(*it)->getWeight()) * (iy - jy)/8;
      }
    }
  }

}

// Check if NPC has collided with any of the level's Collidables
void Level::CheckCollision_NPCtoCollidable(std::vector<std::shared_ptr<NPC>>::iterator it)
{
  for (std::vector< std::shared_ptr<Collidable> >::const_iterator kt = collidables.begin(); kt != collidables.end(); ++kt)
  {
    if(Collision::BoundingBoxTest( (*kt)->animatedSprite.hitbox, (*it)->animatedSprite.hitbox ))
     {
        switch( (*kt)->getType() )
        {
          case Collidable::SubwayDoor :
            std::cout << "NPC has entered the subway" << std::endl;
            npc_success_count++;
            (*it)->directions.clear();
            DestroyNPC(it);
            if (it == npc.end()) { return; } // Necessary, otherwise there will be a crash on removing last item from vector
            break;

          case Collidable::SubwayRail :
            std::cout << "NPC has perished" << std::endl;
            DestroyNPC(it);
            if(it == npc.end()) { return; } // Necessary, otherwise there will be a crash on removing last item from vector
            break;

          case Collidable::SubwayPlatform :
            std::cout << "NPC shall not pass" << std::endl;
            if((*it)->directions_it->getSpeed() < 10)
            {
              // npc should avoid subway platforms when walking
              // check current animation, otherwise if thrown on platform npc would get stuck?
              //(*it)->MoveOppo(1);
            }
            break;

          case Collidable::ImmovableObject :
            std::cout << "NPC hit immovable object" << std::endl;
            if((*it)->directions_it->getSpeed() > 10)
            {
              std::cout << "NPC killed by immovable object" << std::endl;
              DestroyNPC(it);
              if (it == npc.end()) { return; }
            }
            else
            {
              (*it)->AddDirectionOppo(1);
            }
            break;
        } //end switch
     } //end collision test
  } //end collidable loop
}
*/

bool Level::Victory()
{
  if(npc_success_count >= victory_requirement && running_time.getElapsedTime() < gameover_time)
    return true;
  else
    return false;
}

bool Level::GameOver()
{
  if (running_time.getElapsedTime() > gameover_time)
    return true;
  else
    return false;
}

float Level::getRunningTime()
{
  return running_time.getElapsedTime().asSeconds();
}

float Level::getGameOverTime()
{
  return gameover_time.asSeconds();
}

