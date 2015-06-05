
#include "level.h"

Level::Level(int id, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data)
  : level_id(id),
    animations(animations),
    data(data),
    bounds(1600.0,1600.0),
    gameover_time(sf::seconds(30.0f)),
    npc_death_count(0)
{

  running_time.restart();

  // clear vectors and deallocate memory
  entities.clear();
  exits.clear();

  // Load Level
  switch (level_id)
  {
    case 1:
      mp.Load("map2.txt");

      // Need to add invisible indestructible wall surrounding level
      CreateCollidable(Collidable::Boundary, 0, 0, 1, bounds.y); // left wall
      CreateCollidable(Collidable::Boundary, bounds.x, 0, 1, bounds.y); // right wall
      CreateCollidable(Collidable::Boundary, 0, 0, bounds.x, 1); // top wall
      CreateCollidable(Collidable::Boundary, 0, bounds.y, bounds.x, 1); // bottom wall
/*
                                                  //  x     y   width  height
      CreateCollidable(Collidable::Indestructible,     0,   300,   30,   200);
      CreateCollidable(Collidable::Indestructible,     0,     0,   30,   268);
      CreateCollidable(Collidable::Indestructible,     0,   500,   30,   300);
      CreateCollidable(Collidable::Indestructible,     0,   269,   30,    30);
      CreateCollidable(Collidable::Indestructible,     0,   469,   30,    30);
      CreateCollidable(Collidable::Indestructible,    30,     0,   50,   800);
      CreateCollidable(Collidable::Indestructible,   500,   500,  100,    10);
*/
      CreateCollidable(Collidable::Exit,             700,   700,  200,   200);
      CreateCollidable(Collidable::Exit,             700,   400,  100,   100);

      CreateNPC(NPC::Goomba, 300, 500);
      CreateNPC(NPC::Chumba, 400, 400);

      CreateWeapon(Weapon::SMG, 200, 100);
      CreateWeapon(Weapon::Pole, 400, 400);
      CreateWeapon(Weapon::Pole, 200, 200);
      CreateWeapon(Weapon::Shotgun, 0, 0);
      CreateWeapon(Weapon::Pistol, 700,700);
      CreateWeapon(Weapon::RocketLauncher, 500,500);

      break;

    case 2:
      mp.Load("map_L2.txt");

      CreateNPC(NPC::Goomba, 200, 200);
      CreateNPC(NPC::Chumba, 400, 400);

      break;

  }

}

// Dynamically creates a new NPC object and returns a smart pointer to it
void Level::CreateNPC(NPC::Type type, double x, double y)
{
  auto p = std::make_shared<NPC>(type, animations, data, x, y);
  entities.push_back(p);
}

// Dynamically creates a new Weapon object and returns a smart pointer to it
void Level::CreateWeapon(Weapon::Type type, double x, double y)
{
  auto p = std::make_shared<Weapon>(type, animations, data, x, y);
  entities.push_back(p);
}

void Level::CreateProjectile(Projectile::Type type, double x, double y, Orientation::Type o)
{
  auto p = std::make_shared<Projectile>(type, animations, data, x, y, o);
  entities.push_back(p);

  if(type == Projectile::BuckShot)
  {
      auto p2 = std::make_shared<Projectile>(type, animations, data, x-15, y-3, o);
      auto p3 = std::make_shared<Projectile>(type, animations, data, x-10, y+3, o);
      auto p4 = std::make_shared<Projectile>(type, animations, data, x+15, y-3, o);
      auto p5 = std::make_shared<Projectile>(type, animations, data, x+10, y+3, o);

      entities.push_back(p2);
      entities.push_back(p3);
      entities.push_back(p4);
      entities.push_back(p5);
  }
}

void Level::CreateCollidable(Collidable::Type type, int x, int y, int width, int height)
{
  auto p = std::make_shared<Collidable>(type, animations, data, x, y, width, height);

  if(type == Collidable::Exit)
    exits.push_back(p);
  else
    entities.push_back(p);
}

void Level::MoveEntities()
{
  for (auto it = entities.begin(); it != entities.end(); ++it)
  {
    (*it)->Move();
  }
}

void Level::DeleteEntities()
{
  for (auto it = entities.begin(); it != entities.end(); )
  {
    if((*it)->getStatus() == AnimatedEntity::Dead && !(*it)->animatedSprite.isPlaying()) // any entity that is declared dead with no active death animation should be deleted
      DestroyObject(entities, it);
    else if(typeid(**it) == typeid(Projectile) && !(*it)->isMoving()) // projectiles that are not moving should be deleted
      DestroyObject(entities, it);
    else
      ++it;
  }

}

template <typename T1, typename T2>
void Level::DestroyObject(T1& vec, T2& it)
{
  // erase remove idiom
  vec.erase(std::remove(vec.begin(), vec.end(), *it),
            vec.end());
}

/*
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
*/

float Level::getRunningTime()
{
  return running_time.getElapsedTime().asSeconds();
}

float Level::getGameOverTime()
{
  return gameover_time.asSeconds();
}


