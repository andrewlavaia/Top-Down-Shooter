
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

  // ANIMATIONS SHOULD GET MOVED TO UPDATE GAME LOGIC SECTION
  // CAN'T MOVE TO DRAW SECTION BECAUSE NEEDS TO STAY IN FIXED TIME STAMP
  // FOR SMOOTH ANIMATIONS


  // Spawning Controls
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
      this->level.npc.push_back(this->level.CreateNPC(NPC::Chumba));
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
      this->level.npc.push_back(this->level.CreateNPC(NPC::Goomba));
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

  // how much the npc moves is based on hero's strength factor, npc's weight and the current distance between hero and npc
  for (unsigned i = 0; i < this->level.npc.size(); ++i)
  {
    if(Collision::BoundingBoxTest(this->level.hero.animatedSprite.hitbox, this->level.npc[i]->animatedSprite.hitbox))
    {
      this->level.npc[i]->position.x += this->level.hero.strength * this->level.npc[i]->weight * (this->level.npc[i]->position.x - this->level.hero.position.x);
      this->level.npc[i]->position.y += this->level.hero.strength * this->level.npc[i]->weight * (this->level.npc[i]->position.y - this->level.hero.position.y);
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
  // Update Window
  // ---------------
  window.display();
}

