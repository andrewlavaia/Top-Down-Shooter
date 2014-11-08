
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
  textures.Load(Textures::NPC, "spritesheet.png");

  if(!font_HUD.loadFromFile("calibri.ttf"))
  {
    //throw exception...
    std::cout<<"Font Not Loaded"<<std::endl;
  }
  text_timer.setFont(font_HUD);
  text_timer.setCharacterSize(40);
  text_timer.setColor(sf::Color::Black);
  text_timer.setPosition(400,20);
}

void Level::Load(int id)
{
  running_time.restart();

  // clear vectors and deallocate memory
  npc.clear(); // std::unique_ptr will delete object automatically, deleting any existing NPCs
  weapons.clear();
  collidables.clear();

  // Load Level
  switch (id)
  {
    case 1:
      mp.Load("map2.txt");
                                                   //  x     y   width  height
      CreateCollidable(Collidable::SubwayDoor,          0,  300,  30,   200);
      CreateCollidable(Collidable::SubwayRail,          0,    0,  30,   268);
      CreateCollidable(Collidable::SubwayRail,          0,  500,  30,   300);
      CreateCollidable(Collidable::ImmovableObject,     0,  269,  30,   31);
      CreateCollidable(Collidable::ImmovableObject,     0,  469,  30,   31);
      CreateCollidable(Collidable::SubwayPlatform,      30,   0,  50,   800);
      CreateCollidable(Collidable::ImmovableObject,     500,  500,  100,  5);

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
  std::unique_ptr<NPC> p_enemy( new NPC(type) );
  p_enemy->CreateAnimations(this->textures);
  npc.push_back( std::move(p_enemy) );
}

// Dynamically creates a new Weapon object and returns a smart pointer to it
void Level::CreateWeapon(Weapon::Type type)
{
 // std::unique_ptr<Weapon> p_weapon( new Weapon(type) );
 // weapon.push_back( std::move(p_weapon) );

  std::shared_ptr<Weapon> w(new Weapon(type));
  weapons.push_back(w);
}

// Dynamically creates a new Collidable object and returns a smart pointer to it
void Level::CreateCollidable(Collidable::Type type, double x, double y, double width, double height)
{
  std::unique_ptr<Collidable> p_collidable( new Collidable(type, x, y, width, height) );
  collidables.push_back( std::move(p_collidable) );
}



void Level::MoveNPCs()
{
  if(hero.grabbed_npc != nullptr)
  {
    hero.grabbed_npc->position.x = hero.position.x;
    hero.grabbed_npc->position.y = hero.position.y - 30;
    // set currentAnimation to "grabbed"
  }

  if (hero.roped_npc != nullptr)
  {
    // don't move
    // set currentAnimation to "roped"
  }


  for (std::vector< std::unique_ptr<NPC> >::iterator it = npc.begin(); it != npc.end(); ++it)
  {
    MoveObject(it);
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
    MoveObject(it);
  }
}

template <typename T>
void Level::MoveObject(T& it)
{
  //random number generator : rand()%(max-min+1) + min
  //std::cout<<obj.position.x << std::endl;
  if((*it)->directions.empty() == true) { return; }

  // Check if object has travelled further than distance set in current Direction object
  if((*it)->distance_travelled > (*it)->directions_it->getDistance())
  {
    // If distance exceeded, reset distance counter and have iterator point to next Direction object
    (*it)->distance_travelled = 0;

    if((*it)->directions_it->isRepeat())
    {
      (*it)->directions_it++;
    }
    else
    {
      (*it)->directions_it = (*it)->directions.erase( (*it)->directions_it );
    }

    // if last direction reached after incrementing iterator, reset to beginning
    if ( (*it)->directions_it == (*it)->directions.end() ) {
      (*it)->directions_it = (*it)->directions.begin();
    }

  }

  // use pythagorean's theorem to calculate distance when heading NE, NW, SE, or SW
  double hypotenuse = sqrt((*it)->directions_it->getSpeed()*(*it)->directions_it->getSpeed() + (*it)->directions_it->getSpeed()*(*it)->directions_it->getSpeed());

  // check direction and move object accordingly
  switch ( (*it)->directions_it->getType() )
  {
    case Orientation::N :
      (*it)->position.y -= (*it)->directions_it->getSpeed();
      (*it)->animatedSprite.setRotation(0);
      break;

    case Orientation::S :
      (*it)->position.y += (*it)->directions_it->getSpeed();
      (*it)->animatedSprite.setRotation(180);
      break;

    case Orientation::E :
      (*it)->position.x += (*it)->directions_it->getSpeed();
      (*it)->animatedSprite.setRotation(90);
      break;

    case Orientation::W :
      (*it)->position.x -= (*it)->directions_it->getSpeed();
      (*it)->animatedSprite.setRotation(270);
      break;

    case Orientation::NW :
      (*it)->position.x -= hypotenuse/2;
      (*it)->position.y -= hypotenuse/2;
      (*it)->animatedSprite.setRotation(315);
      break;

    case Orientation::NE :
      (*it)->position.x += hypotenuse/2;
      (*it)->position.y -= hypotenuse/2;
      (*it)->animatedSprite.setRotation(45);
      break;

    case Orientation::SW :
      (*it)->position.x -= hypotenuse/2;
      (*it)->position.y += hypotenuse/2;
      (*it)->animatedSprite.setRotation(225);
      break;

    case Orientation::SE :
      (*it)->position.x += hypotenuse/2;
      (*it)->position.y += hypotenuse/2;
      (*it)->animatedSprite.setRotation(135);
      break;

  }

  // update distance travelled
  if ( (*it)->directions_it->getType() == Orientation::NW ||
       (*it)->directions_it->getType() == Orientation::NE ||
       (*it)->directions_it->getType() == Orientation::SW ||
       (*it)->directions_it->getType() == Orientation::SE)
  {
    (*it)->distance_travelled += hypotenuse;
  }
  else
  {
    (*it)->distance_travelled += (*it)->directions_it->getSpeed();
  }
}

void Level::DestroyNPC(std::vector<std::unique_ptr<NPC>>::iterator it)
{
  // erase remove idiom
  npc.erase( std::remove(npc.begin(), npc.end(), *it),
                         npc.end() );

}

// Check if NPC has collided with the hero
void Level::CheckCollision_NPCtoHero(std::vector<std::unique_ptr<NPC>>::iterator it)
{
  // if hero hits any npc, npc bumped back (based on hero strength, npc weight, and distance factor)
  if(Collision::BoundingBoxTest(hero.animatedSprite.hitbox, (*it)->animatedSprite.hitbox))
  {
    // Check if NPC was just thrown
    // NOT IMPLEMENTED YET - Check current animation != throw animation
    double ix = (*it)->position.x;
    double iy = (*it)->position.y;
    double jx = hero.position.x;
    double jy = hero.position.y;

    (*it)->position.x += (1/(*it)->getWeight()) * (ix - jx)/2;
    (*it)->position.y += (1/(*it)->getWeight()) * (iy - jy)/2;
  }
}

// Check if NPC has collided with any of the level's other NPCs
void Level::CheckCollision_NPCtoNPC(std::vector<std::unique_ptr<NPC>>::iterator it)
{

  // if any npc runs into another npc, they each are bumped back (based on their weight)
  for (std::vector< std::unique_ptr<NPC> >::iterator jt = npc.begin(); jt != npc.end(); ++jt)
  {
    if(Collision::BoundingBoxTest( (*jt)->animatedSprite.hitbox, (*it)->animatedSprite.hitbox))
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
        (*jt)->position.x += (1/(*jt)->getWeight()) * (jx - ix)/2;
        (*jt)->position.y += (1/(*jt)->getWeight()) * (jy - iy)/2;
      }
      else if(i_force < j_force) // npc *it will be pushed back
      {
        (*it)->position.x += (1/(*it)->getWeight()) * (ix - jx)/2;
        (*it)->position.y += (1/(*it)->getWeight()) * (iy - jy)/2;
      }
      else // i_force = j_force, so both pushed back
      {
        (*jt)->position.x += (1/(*jt)->getWeight()) * (jx - ix)/4;
        (*jt)->position.y += (1/(*jt)->getWeight()) * (jy - iy)/4;
        (*it)->position.x += (1/(*it)->getWeight()) * (ix - jx)/4;
        (*it)->position.y += (1/(*it)->getWeight()) * (iy - jy)/4;


      }
    }
  }

}

// Check if NPC has collided with any of the level's Collidables
void Level::CheckCollision_NPCtoCollidable(std::vector<std::unique_ptr<NPC>>::iterator it)
{
  for (std::vector< std::unique_ptr<Collidable> >::const_iterator kt = collidables.begin(); kt != collidables.end(); ++kt)
  {
    if(Collision::BoundingBoxTest( (*kt)->sprite, (*it)->animatedSprite.hitbox ))
     {
        switch( (*kt)->getType() )
        {
          case Collidable::SubwayDoor :
            std::cout << "NPC has entered the subway" << std::endl;
            npc_success_count++;
            (*it)->directions.clear();
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

              // check current animation?
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
              (*it)->MoveOppo(1);
            }
            break;
        } //end switch
     } //end collision test
  } //end collidable loop
}

bool Level::Victory()
{
  if(npc_success_count >= victory_requirement && running_time.getElapsedTime() < gameover_time)
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

