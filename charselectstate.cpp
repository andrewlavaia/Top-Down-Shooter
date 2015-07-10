
#include "charselectstate.h"
#include "playstate.h"
#include <iostream>

CCharSelectState CCharSelectState::CharSelectState;

void CCharSelectState::Init(CGameEngine* game)
{
  std::cout << "CharSelect State started." << std::endl ;
}

void CCharSelectState::Cleanup()
{
  std::cout << "CharSelect State ended." << std::endl ;
}

void CCharSelectState::Pause()
{

}

void CCharSelectState::Resume()
{

}

void CCharSelectState::HandleEvents(CGameEngine* game)
{
  sf::Event event;
  while (game->window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        game->window.close();
        game->Quit();
        break;
      case sf::Event::KeyPressed:
        game->PushState( CPlayState::Instance() );
        break;
      case sf::Event::MouseButtonPressed:
        game->PushState( CPlayState::Instance() );
        break;
      default:
        //Do Nothing
        break;
    }
  }
}

void CCharSelectState::Update(CGameEngine* game)
{

}

void CCharSelectState::Draw(CGameEngine* game, double interpolation)
{
  game->window.clear();
  game->window.display();

}
