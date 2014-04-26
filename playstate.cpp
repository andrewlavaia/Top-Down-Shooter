
#include "playstate.h"
#include "mapmanager.h"
#include "hero.h"
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
    this->level.hero.x -= this->level.hero.speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    this->level.hero.x += this->level.hero.speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    this->level.hero.y -= this->level.hero.speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    this->level.hero.y += this->level.hero.speed;
  }
}

void CPlayState::Update(CGameEngine* game)
{
  // NPC is not collidable while it is moving
  // how much the npc moves is based on hero's strength factor, npc's weight and the current distance between hero and npc sprite at time of contact

  if(Collision::BoundingBoxTest(this->level.hero.sprite, this->level.npc.sprite) && this->level.npc.collision_flag == false)
  {
    this->level.npc.collision_flag = true;
    this->level.npc.x += this->level.hero.strength * (this->level.npc.sprite.getPosition().x - this->level.hero.sprite.getPosition().x);
    this->level.npc.y += this->level.hero.strength * (this->level.npc.sprite.getPosition().y - this->level.hero.sprite.getPosition().y);
  }
}

void CPlayState::Draw(CGameEngine* game)
{
  // ---------------
  // Initialize Render Window
  // ---------------

  sf::RenderWindow &window = game->window;
  window.clear(sf::Color(0, 240, 255));

  // -------------
  // Draw Tiles
  // -------------

  // note: copying the tilemap initially is much quicker than than the member function calls
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

  // move hero sprite by (current hero location - sprite location) * velocity factor * elapsed time
  double distance_h = this->level.hero.x - this->level.hero.sprite.getPosition().x;
  double distance_v = this->level.hero.y - this->level.hero.sprite.getPosition().y;

  // choose appropriate sprite based on current direction
  if(distance_h > 5) // heading right
  {
    this->level.hero.sprite.setTextureRect(sf::IntRect(40, 0, 20, 20));
  }
  else if(distance_h < -5) // heading left
  {
    this->level.hero.sprite.setTextureRect(sf::IntRect(60, 0, 20, 20));
  }
  else if( distance_v > 5) // heading down
  {
    this->level.hero.sprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
  }
  else if(distance_v < -5) // heading up
  {
    this->level.hero.sprite.setTextureRect(sf::IntRect(20, 0, 20, 20));
  }

  // move and draw hero
  this->level.hero.sprite.move( distance_h * this->level.hero.velocity * game->render_timer.GetCounter()/1000,
                                distance_v * this->level.hero.velocity * game->render_timer.GetCounter()/1000);
  window.draw(this->level.hero.sprite);

  // ---------------
  // Draw NPCs
  // ---------------

  // same movement formula as hero
  double npc_distance_h = this->level.npc.x - this->level.npc.sprite.getPosition().x;
  double npc_distance_v = this->level.npc.y - this->level.npc.sprite.getPosition().y;
  this->level.npc.sprite.move( npc_distance_h * this->level.npc.velocity *  game->render_timer.GetCounter()/1000,
                               npc_distance_v * this->level.npc.velocity * game->render_timer.GetCounter()/1000);

  // if npc sprite is close to target it can be collided with again
  // SHOULD THIS BE MOVED OUT OF RENDER LOOP?
  if(abs(npc_distance_h) < 2 && abs(npc_distance_v) < 2)
  {
    this->level.npc.collision_flag = false;
  }
  window.draw(this->level.npc.sprite);

  // ---------------
  // Update Window
  // ---------------
  window.display();
}

