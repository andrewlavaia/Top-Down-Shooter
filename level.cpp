
#include "level.h"

Level::Level(int id, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data)
  : level_id(id),
    animations(animations),
    data(data),
    bounds(1600.0, 1600.0),
    gameover_time(sf::seconds(120.0f)),
    enemy_death_count(0),
    sheep_pen_count(0),
    sheep_total(0)
{

  running_time.restart();

  // clear vectors and deallocate memory
  entities.clear();

  // Load Level
  switch (level_id)
  {
    case 1:
      mp.Load("map2.txt");


      // Boundaries not really working well. Take out and keave as open map.

      // Need to add invisible indestructible wall surrounding level
      CreateCollidable(Collidable::Boundary, 0, 0, 5, bounds.y); // left wall
      CreateCollidable(Collidable::Boundary, bounds.x, 0, 5, bounds.y); // right wall
      CreateCollidable(Collidable::Boundary, 0, 0, bounds.x, 5); // top wall
      CreateCollidable(Collidable::Boundary, 0, bounds.y, bounds.x, 5); // bottom wall




      /*
      // below code is too slow, as it pushes too many entities into the entity vector, slowing down all operations
      for( int i = 0; i <= bounds.y; i = i + 10 )
      {
        for( int j = 0; j <= bounds.x; j = j + 10 )
        {
          if( i == 0 || j == 0 || i == bounds.y || j == bounds.x )
            CreateCollidable(Collidable::Boundary, i, j, 10, 10);
        }
      }
      */
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

      // add SheepPen(s)
      CreateCollidable( Collidable::SheepPen,        800,   400,  100,   100 );
/*
      // add exits (still relevant?)
      CreateCollidable(Collidable::Exit,             700,   700,  200,   200);
      CreateCollidable(Collidable::Exit,             700,   400,  100,   100);
*/
      // add weapons
      CreateWeapon( Weapon::SMG, rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      //CreateWeapon( Weapon::Pole, rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      //CreateWeapon( Weapon::Pole, rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateWeapon( Weapon::Shotgun, rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateWeapon( Weapon::Rifle, rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateWeapon( Weapon::Pistol, rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateWeapon( Weapon::RocketLauncher, rand() % (int)getBounds().x, rand() % (int)getBounds().y );


      CreateNPC( NPC::Sheep,          rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateNPC( NPC::McGinger,       rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateNPC( NPC::BigRick,        rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateNPC( NPC::UglyAmy,        rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateNPC( NPC::TooCoolJack,    rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateNPC( NPC::DeNiro,         rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateNPC( NPC::Barnaby,        rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateNPC( NPC::ToughSugar,     rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateNPC( NPC::AmbiguousAlex,  rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateNPC( NPC::BaldingSam,     rand() % (int)getBounds().x, rand() % (int)getBounds().y );



      break;

    case 2:
      mp.Load("map_L2.txt");

      CreateNPC( NPC::McGinger, rand() % (int)getBounds().x, rand() % (int)getBounds().y );
      CreateNPC( NPC::BigRick, rand() % (int)getBounds().x, rand() % (int)getBounds().y );

      break;

  }

}

// Dynamically creates a new NPC object and returns a smart pointer to it
void Level::CreateNPC(NPC::Type type, double x, double y)
{
  //create weapon from NPCTable and add to entities if anything other than hand
  auto w = std::make_shared<Weapon>( data.NPCTable[type].weapon, animations, data, x, y );
  if( data.NPCTable[type].weapon == Weapon::Hands )
    w = nullptr;
  else
    entities.push_back(w);

  auto p = std::make_shared<NPC>(type, animations, data, x, y, w);
  entities.push_back(p);

  if( type == NPC::Sheep )
    sheep_total++;
}

// Dynamically creates a new Weapon object and returns a smart pointer to it
void Level::CreateWeapon(Weapon::Type type, double x, double y)
{
  auto p = std::make_shared<Weapon>(type, animations, data, x, y);
  entities.push_back(p);
}
/*
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
*/

void Level::CreateCollidable(Collidable::Type type, int x, int y, int width, int height)
{
  auto p = std::make_shared<Collidable>(type, animations, data, x, y, width, height);

/*  if(type == Collidable::Exit)
    exits.push_back(p);
  else
*/
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
    if( (*it)->getStatus() == AnimatedEntity::Dead && !(*it)->animatedSprite.isPlaying() ) // any entity that is declared dead with no active death animation should be deleted
      DestroyObject(entities, it);
    else if( (*it)->getParentType() == AnimatedEntity::ProjectileType && !(*it)->isMoving() ) // projectiles that are not moving should be deleted
      DestroyObject(entities, it);
    else
      ++it;
  }
}

template <typename T1, typename T2>
void Level::DestroyObject(T1& vec, T2& it)
{
  // erase remove idiom
  vec.erase( std::remove( vec.begin(), vec.end(), *it ), vec.end() );
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


