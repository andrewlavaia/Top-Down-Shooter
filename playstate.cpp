
#include "playstate.h"
#include "mapmanager.h"
#include "hero.h"
#include "timer.h"

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


}

void CPlayState::Draw(CGameEngine* game)
{
  sf::RenderWindow &window = game->window;
  window.clear(sf::Color(0, 240, 255));

  // Draw all the tile sprites
  // note: copying the tilemap initially is much quicker than than the member function calls
  std::vector<std::vector<Tile>> tilemap = this->level.map.GetTiles();
  for(unsigned i = 0; i < tilemap.size(); i++)
  {
    for(unsigned j = 0; j < tilemap[i].size(); j++)
    {
      window.draw(tilemap[i][j].sprite);
    }
  }


  // move hero sprite by (current hero location - sprite location) * velocity factor * elapsed time

  double distance_h = this->level.hero.x - this->level.hero.sprite.getPosition().x;
  double distance_v = this->level.hero.y - this->level.hero.sprite.getPosition().y;
  if(distance_h > 5) // heading right
  {
    this->level.hero.sprite.setTextureRect(sf::IntRect(40, 0, 20, 20));
  }
  if(distance_h < -5) // heading left
  {
    this->level.hero.sprite.setTextureRect(sf::IntRect(60, 0, 20, 20));
  }
  if( distance_v > 5) // heading down
  {
    this->level.hero.sprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
  }
  if(distance_v < -5) // heading up
  {
    this->level.hero.sprite.setTextureRect(sf::IntRect(20, 0, 20, 20));
  }

  this->level.hero.sprite.move( distance_h * level.hero.velocity * game->render_timer.GetCounter()/1000,
                                distance_v * level.hero.velocity * game->render_timer.GetCounter()/1000);



  window.draw(this->level.hero.sprite);

  window.display();
}

