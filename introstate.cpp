
#include "introstate.h"
#include "charselectstate.h"
#include <iostream>

CIntroState CIntroState::IntroState;

void CIntroState::Init(CGameEngine* game)
{
  std::cout << "Intro State started." << std::endl ;

  header1.setFont( fonts.get( Fonts::Calibri ) );
  header1.setColor( sf::Color::Blue );
  header1.setPosition( 50, 150 );
  header2.setFont( fonts.get( Fonts::Calibri ) );
  header2.setColor( sf::Color::Blue );
  header2.setPosition( 50, 200 );
  header3.setFont( fonts.get( Fonts::Calibri ) );
  header3.setColor( sf::Color::Blue );
  header3.setPosition( 50, 250 );

  header1.setString( "Congratulations young man, you just inherited a sheep farm.");
  header2.setString( "Your job is to protect your sheep as long as you possibly can." );
  header3.setString( "Good luck..." );
}

void CIntroState::Cleanup()
{
  std::cout << "Intro State ended." << std::endl ;
}

void CIntroState::Pause(CGameEngine* game)
{

}

void CIntroState::Resume(CGameEngine* game)
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
  game->window.clear( sf::Color::White );
  game->window.draw( header1 );
  game->window.draw( header2 );
  game->window.draw( header3 );
  game->window.display();

}
