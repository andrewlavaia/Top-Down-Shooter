
#include "level.h"
#include <math.h> // sqrt

Level::Level()
{
  textures.Load(Textures::Hero, "spritesheet.png");
  textures.Load(Textures::NPC, "character-sprite-map.gif");
}

void Level::Load(int id)
{

  // Delete all existing NPCs and deallocate memory
  npc.clear(); // std::unique_ptr will delete pointed to object automatically
  weapon.clear();

  // Load Level
  switch (id)
  {
    case 1:
      mp.Load("map2.txt");

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
  std::unique_ptr<Weapon> p_weapon( new Weapon(type) );
  weapon.push_back( std::move(p_weapon) );
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

    /*

    //this->level.npc[i]->position.x += ((rand()%3)-1) * this->level.npc[i]->speed; // [-1,0,1] * speed
    //std::cout << level.npc[i]->distance_travelled << " - " << this->level.npc[i]->directions[this->level.npc[i]->direction_it].getDistance() << std::endl;
    if( (*it)->directions.empty() != true )
    {

      // Check if NPC has travelled further than distance set in current Direction object
      if( (*it)->distance_travelled > (*it)->directions_it->getDistance() )
      {
        // If distance exceeded, reset distance counter and have iterator point to next Direction object
        (*it)->distance_travelled = 0;

        if((*it)->directions_it->isRepeat())
          (*it)->directions_it++;
        else
          (*it)->directions_it = (*it)->directions.erase( (*it)->directions_it );


        // if last direction reached after incrementing iterator, reset to beginning
        if ( (*it)->directions_it == (*it)->directions.end() )
          (*it)->directions_it = (*it)->directions.begin();

      }

      // use pythagorean's theorem to calculate distance when heading NE, NW, SE, or SW
      double hypotenuse = sqrt((*it)->directions_it->getSpeed()*(*it)->directions_it->getSpeed() + (*it)->directions_it->getSpeed()*(*it)->directions_it->getSpeed());

      // check direction and move npc accordingly
        switch ( (*it)->directions_it->getType() )
        {
          case Orientation::N :
            (*it)->position.y -= (*it)->directions_it->getSpeed();
            break;

          case Orientation::S :
            (*it)->position.y += (*it)->directions_it->getSpeed();
            break;

          case Orientation::E :
            (*it)->position.x += (*it)->directions_it->getSpeed();
            break;

          case Orientation::W :
            (*it)->position.x -= (*it)->directions_it->getSpeed();
            break;

          case Orientation::NW :
            (*it)->position.x -= hypotenuse/2;
            (*it)->position.y -= hypotenuse/2;
            break;

          case Orientation::NE :
            (*it)->position.x += hypotenuse/2;
            (*it)->position.y -= hypotenuse/2;
            break;

          case Orientation::SW :
            (*it)->position.x -= hypotenuse/2;
            (*it)->position.y += hypotenuse/2;
            break;

          case Orientation::SE :
            (*it)->position.x += hypotenuse/2;
            (*it)->position.y += hypotenuse/2;
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

    } // end directions.size() > 0 check

    */
  } // end NPC loop

}

void Level::MoveWeapons()
{
  if (hero.weapon != nullptr)
  {
    hero.weapon->position = hero.position;
  }

  for (std::vector< std::unique_ptr<Weapon> >::iterator it = weapon.begin(); it != weapon.end(); ++it)
  {
    MoveObject(it);
    /*
    if( (*it)->directions.empty() != true)
    {
      // Check if Weapon has travelled further than distance set in current Direction object
      if( (*it)->distance_travelled > (*it)->directions_it->getDistance() )
      {
        // If distance exceeded, reset distance counter and have iterator point to next Direction object
        (*it)->distance_travelled = 0;

        if((*it)->directions_it->isRepeat())
          (*it)->directions_it++;
        else
          (*it)->directions_it = (*it)->directions.erase( (*it)->directions_it );


        // if last direction reached after incrementing iterator, reset to beginning
        if ( (*it)->directions_it == (*it)->directions.end() )
          (*it)->directions_it = (*it)->directions.begin();

      }

      // use pythagorean's theorem to calculate distance when heading NE, NW, SE, or SW
      double hypotenuse = sqrt((*it)->directions_it->getSpeed()*(*it)->directions_it->getSpeed() + (*it)->directions_it->getSpeed()*(*it)->directions_it->getSpeed());

      // check direction and move npc accordingly
        switch ( (*it)->directions_it->getType() )
        {
          case Orientation::N :
            (*it)->position.y -= (*it)->directions_it->getSpeed();
            break;

          case Orientation::S :
            (*it)->position.y += (*it)->directions_it->getSpeed();
            break;

          case Orientation::E :
            (*it)->position.x += (*it)->directions_it->getSpeed();
            break;

          case Orientation::W :
            (*it)->position.x -= (*it)->directions_it->getSpeed();
            break;

          case Orientation::NW :
            (*it)->position.x -= hypotenuse/2;
            (*it)->position.y -= hypotenuse/2;
            break;

          case Orientation::NE :
            (*it)->position.x += hypotenuse/2;
            (*it)->position.y -= hypotenuse/2;
            break;

          case Orientation::SW :
            (*it)->position.x -= hypotenuse/2;
            (*it)->position.y += hypotenuse/2;
            break;

          case Orientation::SE :
            (*it)->position.x += hypotenuse/2;
            (*it)->position.y += hypotenuse/2;
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
    } // end directions.size() > 0 check
    */
  } // end Weapon loop

}


template <typename T>
void Level::MoveObject(T& it)
{
  //random number generator : rand()%(max-min+1) + min
  //std::cout<<obj.position.x << std::endl;
  if( (*it)->directions.empty() != true )
  {

    // Check if NPC has travelled further than distance set in current Direction object
    if( (*it)->distance_travelled > (*it)->directions_it->getDistance() )
    {
      // If distance exceeded, reset distance counter and have iterator point to next Direction object
      (*it)->distance_travelled = 0;

      if((*it)->directions_it->isRepeat())
        (*it)->directions_it++;
      else
        (*it)->directions_it = (*it)->directions.erase( (*it)->directions_it );


      // if last direction reached after incrementing iterator, reset to beginning
      if ( (*it)->directions_it == (*it)->directions.end() )
        (*it)->directions_it = (*it)->directions.begin();

    }

    // use pythagorean's theorem to calculate distance when heading NE, NW, SE, or SW
    double hypotenuse = sqrt((*it)->directions_it->getSpeed()*(*it)->directions_it->getSpeed() + (*it)->directions_it->getSpeed()*(*it)->directions_it->getSpeed());

    // check direction and move npc accordingly
      switch ( (*it)->directions_it->getType() )
      {
        case Orientation::N :
          (*it)->position.y -= (*it)->directions_it->getSpeed();
          break;

        case Orientation::S :
          (*it)->position.y += (*it)->directions_it->getSpeed();
          break;

        case Orientation::E :
          (*it)->position.x += (*it)->directions_it->getSpeed();
          break;

        case Orientation::W :
          (*it)->position.x -= (*it)->directions_it->getSpeed();
          break;

        case Orientation::NW :
          (*it)->position.x -= hypotenuse/2;
          (*it)->position.y -= hypotenuse/2;
          break;

        case Orientation::NE :
          (*it)->position.x += hypotenuse/2;
          (*it)->position.y -= hypotenuse/2;
          break;

        case Orientation::SW :
          (*it)->position.x -= hypotenuse/2;
          (*it)->position.y += hypotenuse/2;
          break;

        case Orientation::SE :
          (*it)->position.x += hypotenuse/2;
          (*it)->position.y += hypotenuse/2;
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
}
