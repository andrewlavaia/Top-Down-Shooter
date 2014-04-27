
#include "playstate.h"
#include "mapmanager.h"
#include "hero.h"
#include "npc.h"
#include "timer.h"
#include "collision.h"

CPlayState CPlayState::PlayState;

void CPlayState::Init()
{
  std::cout << "Play State started." << std::endl ;
}

void CPlayState::Cleanup()
{
  std::cout << "Play State ended." << std::endl ;
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
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    this->level.hero.position.x -= this->level.hero.speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    this->level.hero.position.x += this->level.hero.speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    this->level.hero.position.y -= this->level.hero.speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    this->level.hero.position.y += this->level.hero.speed;
  }
}

void CPlayState::Update(CGameEngine* game)
{
  // ---------------
  // Collision Rules
  // ---------------

  // how much the npc moves is based on hero's strength factor, npc's weight and the current distance between hero and npc
  for (unsigned i = 0; i < this->level.npc.size(); ++i)
  {
    if(Collision::BoundingBoxTest(this->level.hero.sprite, this->level.npc[i].sprite))
    {
      this->level.npc[i].position.x += this->level.hero.strength * this->level.npc[i].weight * (this->level.npc[i].position.x - this->level.hero.position.x);
      this->level.npc[i].position.y += this->level.hero.strength * this->level.npc[i].weight * (this->level.npc[i].position.y - this->level.hero.position.y);
    }
  }
}

void CPlayState::Draw(CGameEngine* game, double interpolation)
{
  // ---------------
  // Initialize Render Window
  // ---------------

  sf::RenderWindow &window = game->window;
  window.clear(sf::Color(0, 240, 255));

  // -------------
  // Draw Tiles
  // -------------

  // note: copying the tilemap initially is much quicker than using the member function calls
  std::vector<std::vector<Tile>> tilemap = this->level.map.GetTiles();
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

  this->level.hero.MoveSprite(interpolation);
  window.draw(this->level.hero.sprite);

  // ---------------
  // Draw NPCs
  // ---------------


  for (unsigned i = 0; i < this->level.npc.size(); ++i)
  {
    this->level.npc[i].MoveSprite(interpolation);
    window.draw(this->level.npc[i].sprite);
  }

  // ---------------
  // Update Window
  // ---------------
  window.display();
}

