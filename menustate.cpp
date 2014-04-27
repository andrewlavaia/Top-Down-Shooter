

#include "menustate.h"
#include "introstate.h"
#include "highscorestate.h"
#include <iostream>


CMenuState CMenuState::MenuState;

void CMenuState::Init()
{
  std::cout << "Menu State started." << std::endl;
}

void CMenuState::Cleanup()
{
  std::cout << "Menu State ended." << std::endl ;
}

void CMenuState::Pause()
{

}

void CMenuState::Resume()
{

}

void CMenuState::HandleEvents(CGameEngine* game)
{
  sf::Event event;
  while (game->window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        game->window.close();
        game->Quit();
        break;
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Space) {
            game->PushState( CIntroState::Instance() );
        }
        break;
      case sf::Event::MouseButtonPressed:
        if(event.mouseButton.button == sf::Mouse::Left) {
              game->PushState( CHighScoreState::Instance() );
        }
        break;
      default:
        //Do Nothing
        break;
    }
  }
}

void CMenuState::Update(CGameEngine* game)
{

}

void CMenuState::Draw(CGameEngine* game, double interpolation)
{

}
