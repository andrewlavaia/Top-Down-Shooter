
#include "highscorestate.h"
#include <iostream>


CHighScoreState CHighScoreState::HighScoreState;

void CHighScoreState::Init(CGameEngine* game)
{
  std::cout << "High Score State started." << std::endl;

  header.setFont( fonts.get( Fonts::Calibri ) );
  header.setColor( sf::Color::Blue );
  header.setPosition( 50, 150 );
  header.setString( "High Scores" );
}

void CHighScoreState::Cleanup()
{
  std::cout << "High Score State ended." << std::endl;
}

void CHighScoreState::Pause()
{

}

void CHighScoreState::Resume()
{

}

void CHighScoreState::HandleEvents(CGameEngine* game)
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

void CHighScoreState::Update(CGameEngine* game)
{

}

void CHighScoreState::Draw(CGameEngine* game, double interpolation)
{
  game->window.clear( sf::Color::White );
  game->window.draw( header );
  game->window.display();
}
