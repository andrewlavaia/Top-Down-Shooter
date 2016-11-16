
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

      // add weapons
      CreateWeapon(Weapon::SMG, getRandomNearbyLocation(sf::Vector2f(100,100)));
      CreateWeapon(Weapon::Shotgun, getRandomNearbyLocation(sf::Vector2f(100,100)));
      CreateWeapon(Weapon::Rifle, getRandomNearbyLocation(sf::Vector2f(100,100)));
      CreateWeapon(Weapon::Pistol, getRandomNearbyLocation(sf::Vector2f(100,100)));
      CreateWeapon(Weapon::RocketLauncher, getRandomNearbyLocation(sf::Vector2f(100,100)));
      CreateWeapon(Weapon::Spear, getRandomNearbyLocation(sf::Vector2f(100,100)));

      CreateNPC( NPC::Sheep, sf::Vector2f(100,100) );
      spawnNPCs(10, sf::Time::Zero, sf::Vector2f(100,100));

      break;

    case 2:
      // never implemented other levels...


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

void Level::CreateCollidable(Collidable::Type type, int x, int y, int width, int height)
{
  auto p = std::make_shared<Collidable>(type, animations, data, x, y, width, height);
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

  unsigned long seed =
    std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();

  auto r = std::bind(Distribution(-500, 500), Engine(seed));

  sf::Vector2f coord = sf::Vector2f(location.x + r(), location.y + r());

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
    }
    resetSpawnCooldown();
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

