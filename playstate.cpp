
#include "playstate.h"
#include "mapmanager.h"
#include "hero.h"
#include "npc.h"
#include "timer.h"
#include "collision.h"


CPlayState CPlayState::PlayState;

void CPlayState::Init()
{
  std::cout << "Play State started." << std::endl;
  this->level.Load(1);
  std::cout << "Level 1 Loaded." << std::endl;
}

void CPlayState::Cleanup()
{
  std::cout << "Play State ended." << std::endl;
}

void CPlayState::Pause()
{

}

void CPlayState::Resume()
{

}

void CPlayState::HandleEvents(CGameEngine* game)
{
  sf::Event event;
  this->noKeyPressed = true;

  // ---------------
  // Window Events
  // ---------------
  while (game->window.pollEvent(event))
  {
    switch (event.type)
    {
      case sf::Event::Closed:
        game->window.close();
        game->Quit();
        break;
      default:
        //Do Nothing
        break;
    }
  }

  // -----------------
  // Keyboard Events
  // -----------------
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    this->level.hero.position.x -= this->level.hero.speed;
    this->level.hero.currentAnimation = &this->level.hero.walkAnimationLeft;
    noKeyPressed = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    this->level.hero.position.x += this->level.hero.speed;
    this->level.hero.currentAnimation = &this->level.hero.walkAnimationRight;
    noKeyPressed = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    this->level.hero.position.y -= this->level.hero.speed;
    this->level.hero.currentAnimation = &this->level.hero.walkAnimationUp;
    noKeyPressed = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    this->level.hero.position.y += this->level.hero.speed;
    this->level.hero.currentAnimation = &this->level.hero.walkAnimationDown;
    noKeyPressed = false;
  }

  // Dodge Left
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    this->level.hero.position.x -= this->level.hero.speed * 3;
    noKeyPressed = false;
  }
  // Dodge Right
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    this->level.hero.position.x += this->level.hero.speed * 3;
    noKeyPressed = false;
  }
  // Dodge Down
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    this->level.hero.position.y += this->level.hero.speed * 3;
    noKeyPressed = false;
  }
  // Dodge Up
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    this->level.hero.position.y -= this->level.hero.speed * 3;
    noKeyPressed = false;
  }

  // Pickup Weapon
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
    this->level.hero.PickupWeapon(this->level.weapon);
  }

  // Drop Weapon
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
    this->level.hero.DropWeapon(this->level.weapon);
  }

  // Spawning Controls
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
    this->level.CreateNPC(NPC::Chumba);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
    this->level.CreateNPC(NPC::Goomba);
  }

  // Load next level
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
    this->level.Load(2);
  }

}

void CPlayState::Update(CGameEngine* game)
{
  // Reset Animation Clock
  game->frameTime = game->frameClock.restart();

  // ---------------
  // Collision Tests
  // ---------------

  for (unsigned i = 0; i < this->level.npc.size(); ++i)
  {
    // if hero hits any npc (based on hero strength, npc weight, and distance factor)
    if(Collision::BoundingBoxTest(this->level.hero.animatedSprite.hitbox, this->level.npc[i]->animatedSprite.hitbox))
    {
      this->level.npc[i]->position.x += this->level.hero.strength * (1/this->level.npc[i]->weight) * (this->level.npc[i]->position.x - this->level.hero.position.x);
      this->level.npc[i]->position.y += this->level.hero.strength * (1/this->level.npc[i]->weight) * (this->level.npc[i]->position.y - this->level.hero.position.y);
    }

    // if any npc runs into another npc (based on weight of each npc)
    for (unsigned j = 0; j <this->level.npc.size(); ++j)
    {
      if(Collision::BoundingBoxTest(this->level.npc[j]->animatedSprite.hitbox, this->level.npc[i]->animatedSprite.hitbox))
      {
        // initialize variables so that
        int ix = this->level.npc[i]->position.x;
        int iy = this->level.npc[i]->position.y;
        int jx = this->level.npc[j]->position.x;
        int jy = this->level.npc[j]->position.y;

        this->level.npc[i]->position.x += (1/this->level.npc[i]->weight) * (ix - jx);
        this->level.npc[i]->position.y += (1/this->level.npc[i]->weight) * (iy - jy);

        this->level.npc[j]->position.x += (1/this->level.npc[j]->weight) * (jx - ix);
        this->level.npc[j]->position.y += (1/this->level.npc[j]->weight) * (jy - iy);
      }
    }
  }

  // -------------------
  // Hero Animation
  // -------------------

  this->level.hero.animatedSprite.play(*this->level.hero.currentAnimation);
  for (unsigned i = 0; i < this->level.npc.size(); ++i) {
    this->level.npc[i]->animatedSprite.play(*this->level.npc[i]->currentAnimation);
  }

  if (this->noKeyPressed) {
    this->level.hero.animatedSprite.stop();
  }

  // -------------------
  // NPC AI and Movement
  // -------------------

  for (unsigned i = 0; i < this->level.npc.size(); ++i)
  {
    //random number generator : rand()%(max-min+1) + min
    //this->level.npc[i]->position.x += ((rand()%3)-1) * this->level.npc[i]->speed; // [-1,0,1] * speed
    //std::cout << level.npc[i]->distance_travelled << " - " << this->level.npc[i]->directions[this->level.npc[i]->direction_it].getDistance() << std::endl;

    // Fetch current direction
    Direction d = *this->level.npc[i]->directions_it;

    // Check if NPC has travelled further than distance set in Direction object
    if(this->level.npc[i]->distance_travelled > d.getDistance())
    {
      //this->level.npc[i]->animatedSprite.rotate(this->level.npc[i]->directions.front().angle);

      // If distance exceeded, reset distance counter and increment iterator
      this->level.npc[i]->distance_travelled = 0;
      this->level.npc[i]->directions_it++;

      // if iterator points to end of vector, reset to beginning
      if (this->level.npc[i]->directions_it == this->level.npc[i]->directions.end())
      {
        this->level.npc[i]->directions_it = this->level.npc[i]->directions.begin();
      }

    }
    else // check direction and move npc accordingly
    {

      switch (d.getType())
      {
        case Direction::Up :
          this->level.npc[i]->position.y -= this->level.npc[i]->speed;
          break;

        case Direction::Down :
          this->level.npc[i]->position.y += this->level.npc[i]->speed;
          break;

        case Direction::Right :
          this->level.npc[i]->position.x += this->level.npc[i]->speed;
          break;

        case Direction::Left :
          this->level.npc[i]->position.x -= this->level.npc[i]->speed;
          break;

        case Direction::Up_Left :
          this->level.npc[i]->position.x -= this->level.npc[i]->speed/2;
          this->level.npc[i]->position.y -= this->level.npc[i]->speed/2;
          break;

        case Direction::Up_Right :
          this->level.npc[i]->position.x += this->level.npc[i]->speed/2;
          this->level.npc[i]->position.y -= this->level.npc[i]->speed/2;
          break;

        case Direction::Down_Left :
          this->level.npc[i]->position.x -= this->level.npc[i]->speed/2;
          this->level.npc[i]->position.y += this->level.npc[i]->speed/2;
          break;

        case Direction::Down_Right :
          this->level.npc[i]->position.x += this->level.npc[i]->speed/2;
          this->level.npc[i]->position.y += this->level.npc[i]->speed/2;
          break;

        case Direction::Pause :
          //do nothing;
          break;
      }

      this->level.npc[i]->distance_travelled += this->level.npc[i]->speed;

    } // end else
  } // end NPC loop

} // end CPlayState::Update


void CPlayState::Draw(CGameEngine* game, double interpolation)
{
  // ---------------
  // Initialize Render Window
  // ---------------

  sf::RenderWindow &window = game->window;
  window.clear(sf::Color(255, 255, 255));

  // -------------
  // Draw Tiles
  // -------------

  // note: copying the tilemap initially is much quicker than using the member function calls in loop
  std::vector<std::vector<Tile>> tilemap = this->level.mp.GetTiles();
  for(unsigned i = 0; i < tilemap.size(); i++)
  {
    for(unsigned j = 0; j < tilemap[i].size(); j++)
    {
      window.draw(tilemap[i][j].sprite);
    }
  }

  // -------------
  // Draw Hero
  // -------------

  this->level.hero.animatedSprite.update(game->frameTime);
  this->level.hero.MoveAnimatedSprite(interpolation);
  window.draw(this->level.hero.animatedSprite);
  window.draw(this->level.hero.animatedSprite.hitbox); // debug only

  // ---------------
  // Draw NPCs
  // ---------------

  for (unsigned i = 0; i < this->level.npc.size(); ++i)
  {
    this->level.npc[i]->animatedSprite.update(game->frameTime);
    this->level.npc[i]->MoveAnimatedSprite(interpolation);
    window.draw(this->level.npc[i]->animatedSprite);
    window.draw(this->level.npc[i]->animatedSprite.hitbox); // debug only
  }

  // ---------------
  // Draw Weapons
  // ---------------
  window.draw(this->level.hero.weapon->sprite);

/*
  for (std::vector< std::unique_ptr<Weapon> >::const_iterator it = this->level.weapon.begin(); it != this->level.weapon.end(); it++)
  {
    window.draw( (**it).sprite );
  }
*/

  // ---------------
  // Update Window
  // ---------------
  window.display();
}

