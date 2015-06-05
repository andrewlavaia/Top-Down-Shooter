
#include "optionstate.h"
#include <iostream>


COptionState COptionState::OptionState;

void COptionState::Init(CGameEngine* game)
{
  std::cout << "Option State started." << std::endl;
}

void COptionState::Cleanup()
{
  std::cout << "Option State ended." << std::endl;
}

void COptionState::Pause()
{

}

void COptionState::Resume()
{

}

void COptionState::HandleEvents(CGameEngine* game)
{
  sf::Event event;
  while (game->window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        game->window.close();
        game->Quit();
        break;
      case sf::Event::KeyPressed:
        game->PopState();
        break;
      case sf::Event::MouseButtonPressed:
        game->PopState();
        break;
      default:
        //Do Nothing
        break;
    }
  }
}

void COptionState::Update(CGameEngine* game)
{

}

void COptionState::Draw(CGameEngine* game, double interpolation)
{
  game->window.clear();
  game->window.display();
}
