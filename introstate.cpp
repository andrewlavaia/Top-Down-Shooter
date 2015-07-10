
#include "introstate.h"
#include "charselectstate.h"
#include <iostream>

CIntroState CIntroState::IntroState;

void CIntroState::Init(CGameEngine* game)
{
  std::cout << "Intro State started." << std::endl ;
}

void CIntroState::Cleanup()
{
  std::cout << "Intro State ended." << std::endl ;
}

void CIntroState::Pause()
{

}

void CIntroState::Resume()
{

}

void CIntroState::HandleEvents(CGameEngine* game)
{
  sf::Event event;
  while (game->window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        game->window.close();
        game->Quit();
        break;
      case sf::Event::KeyPressed:
        game->PushState( CCharSelectState::Instance() );
        break;
      case sf::Event::MouseButtonPressed:
        game->PushState( CCharSelectState::Instance() );
        break;
      default:
        //Do Nothing
        break;
    }
  }
}

void CIntroState::Update(CGameEngine* game)
{

}

void CIntroState::Draw(CGameEngine* game, double interpolation)
{
  game->window.clear();
  game->window.display();

}
