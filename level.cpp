
#include "level.h"

Level::Level(int id, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data)
  : level_id(id),
    animations(animations),
    data(data),
    bounds(1600.0, 1600.0),
    enemy_death_count(0),
    sheep_pen_count(0),
    sheep_total(0),
    spawn_cooldown(sf::milliseconds(-1)),
    spawn_count(0)
{

  // clear vectors and deallocate memory
  entities.clear();

  // position background off screen
  background.setPosition(-1000, -1000);

  // Load Level
  switch (level_id)
  {
    case 1:
      mp.Load("map2.txt");


      // Boundaries not really working well. Take out and keave as open map.

      /*
      // Need to add invisible indestructible wall surrounding level
      CreateCollidable(Collidable::Boundary, 0, 0, 5, bounds.y); // left wall
      CreateCollidable(Collidable::Boundary, bounds.x, 0, 5, bounds.y); // right wall
      CreateCollidable(Collidable::Boundary, 0, 0, bounds.x, 5); // top wall
      CreateCollidable(Collidable::Boundary, 0, bounds.y, bounds.x, 5); // bottom wall
      */



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
      CreateWeapon(Weapon::SMG, getRandomNearbyLocation(sf::Vector2f(100,100)));
      CreateWeapon(Weapon::Shotgun, getRandomNearbyLocation(sf::Vector2f(100,100)));
      CreateWeapon(Weapon::Rifle, getRandomNearbyLocation(sf::Vector2f(100,100)));
      CreateWeapon(Weapon::Pistol, getRandomNearbyLocation(sf::Vector2f(100,100)));
      CreateWeapon(Weapon::RocketLauncher, getRandomNearbyLocation(sf::Vector2f(100,100)));


      CreateNPC( NPC::Sheep, sf::Vector2f(100,100) );
      //set spawncooldown to -5
      spawnNPCs(10, sf::Time::Zero, sf::Vector2f(100,100));
      /*
      CreateRandomNPC(sf::Vector2f(100,100));
      CreateRandomNPC(sf::Vector2f(200,200));
      CreateRandomNPC(sf::Vector2f(300,300));
      CreateRandomNPC(sf::Vector2f(400,400));
      CreateRandomNPC(sf::Vector2f(500,500));
      CreateRandomNPC(sf::Vector2f(600,600));
      CreateRandomNPC(sf::Vector2f(700,700));
      CreateRandomNPC(sf::Vector2f(800,800));
      */
      /*
      CreateNPC( NPC::McGinger, sf::Vector2f(200,200) );
      CreateNPC( NPC::BigRick, sf::Vector2f(300,300) );
      CreateNPC( NPC::UglyAmy, sf::Vector2f(400,400) );
      CreateNPC( NPC::TooCoolJack, sf::Vector2f(500,500) );
      CreateNPC( NPC::DeNiro, sf::Vector2f(1000,1000) );
      CreateNPC( NPC::Barnaby, sf::Vector2f(600,600) );
      CreateNPC( NPC::ToughSugar, sf::Vector2f(700,700) );
      CreateNPC( NPC::AmbiguousAlex, sf::Vector2f(800,800) );
      CreateNPC( NPC::BaldingSam, sf::Vector2f(900,900) );
      */


      break;

    case 2:
      mp.Load("map_L2.txt");

      CreateNPC( NPC::McGinger, sf::Vector2f(500,500) );
      CreateNPC( NPC::BigRick, sf::Vector2f(100,100) );

      break;

  }

}

// Dynamically creates a new NPC object and returns a smart pointer to it
void Level::CreateNPC(NPC::Type type, sf::Vector2f coord)
{
  //create weapon from NPCTable and add to entities if anything other than hand
  auto w = std::make_shared<Weapon>( getRandomWeaponType(), animations, data, coord.x, coord.y );
  if( data.NPCTable[type].weapon == Weapon::Hands )
    w = nullptr;
  else
    entities.push_back(w);

  auto p = std::make_shared<NPC>(type, animations, data, coord.x, coord.y, w);
  entities.push_back(p);

  if( type == NPC::Sheep )
    sheep_total++;

  spawn_count++;
}

// Dynamically creates a new NPC object and returns a smart pointer to it
void Level::CreateRandomNPC(sf::Vector2f location)
{
  CreateNPC(getRandomNPCType(), getRandomNearbyLocation(location));
}

// Dynamically creates a new Weapon object and returns a smart pointer to it
void Level::CreateWeapon(Weapon::Type type, sf::Vector2f location)
{
  auto p = std::make_shared<Weapon>(type, animations, data, location.x, location.y);
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

sf::Vector2f Level::getRandomNearbyLocation(sf::Vector2f location)
{
  typedef std::mt19937                                 Engine;
  typedef std::uniform_real_distribution<float>        Distribution;

  //!!! Need a better random seed
  // needs to update faster than milliseconds so that I can spawn multiple random items at once
  // OR add a 1 millisec delay to spawn function?

  unsigned long seed =
    std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();

  auto r = std::bind(Distribution(-500, 500), Engine(seed));

  //std::cout << "Random Coord " << location.x + r() << "," << location.y + r() << std::endl;
  sf::Vector2f coord = sf::Vector2f(location.x + r(), location.y + r());
  //std::cout<<"coord1 " <<coord.x<<","<<coord.y<<std::endl;
  //std::cout<<"coord2 " <<location.x + r()<<","<<location.y+r()<<std::endl;

  sf::sleep(sf::milliseconds(1)); //need to wait 1 millisecond because random seed is based on milliseconds
  return coord;

}

void Level::spawnNPCs(unsigned n, sf::Time dt, sf::Vector2f location)
{
  if( canSpawn() )
  {
    for(auto i = 0; i < n; i++)
    {
      CreateRandomNPC( getRandomNearbyLocation( location ) );
      //std::cout<<"NPC spawned"<<std::endl;
    }
    resetSpawnCooldown();
    //getRandomWeaponType();
  }
  reduceSpawnCooldown(dt);
}

void Level::reduceSpawnCooldown(sf::Time dt)
{
  spawn_cooldown -= dt;
}

void Level::resetSpawnCooldown()
{
  spawn_cooldown = sf::seconds(10);
}

bool Level::canSpawn()
{
  return spawn_cooldown < sf::Time::Zero;
}

Weapon::Type Level::getRandomWeaponType()
{
  Weapon::Type w = static_cast<Weapon::Type>(rand() % Weapon::TypeCount);
  return w;
}

NPC::Type Level::getRandomNPCType()
{
  NPC::Type n = static_cast<NPC::Type>(rand() % NPC::TypeCount);
  return n;
}

