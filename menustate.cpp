

#include "menustate.h"
#include "introstate.h"
#include "highscorestate.h"
#include "optionstate.h"
#include <iostream>

CMenuState CMenuState::MenuState;

void CMenuState::Init(CGameEngine* game)
{
  std::cout << "Menu State started." << std::endl;

}

void CMenuState::Cleanup()
{
  std::cout << "Menu State ended." << std::endl ;
}

void CMenuState::Pause(CGameEngine* game)
{

}

void CMenuState::Resume(CGameEngine* game)
{

}

void CMenuState::HandleEvents(CGameEngine* game)
{
  sf::Event event;

  while (game->window.pollEvent(event)) {

    menu.HandleEvent( event );

    switch (event.type) {

      case sf::Event::Closed:
        game->window.close();
        game->Quit();
        break;

      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Space) {
            game->PushState( CIntroState::Instance() );
        }
        if (event.key.code == sf::Keyboard::BackSpace) {
              //ShowWindow(game->window.getSystemHandle(), SW_MINIMIZE);
              //ShowWindow(game->window.getSystemHandle(), SW_RESTORE);
        }
        break;

      case sf::Event::MouseButtonReleased:

        // Check if main menu button was clicked
        switch( menu.getState() )
        {
          case MainMenu::Menu :
            // do nothing
            break;
          case MainMenu::Intro :
            game->PushState( CIntroState::Instance() );
            break;
          case MainMenu::HighScore :
            game->PushState( CHighScoreState::Instance() );
            break;
          case MainMenu::Option :
            game->PushState( COptionState::Instance() );
            break;
          case MainMenu::Exit :
            game->Quit();
            break;
        }

      default:

        break;
    }

  }

}

void CMenuState::Update(CGameEngine* game)
{
  menu.Update();
}

void CMenuState::Draw(CGameEngine* game, double interpolation)
{

  // ---------------
  // Update Window
  // ---------------

  // Draw something to initialize SFML render engine
  sf::CircleShape shape( 50 );
  game->window.draw( shape );

  game->window.clear();
  menu.Render( game->window );
  game->window.display();

}
