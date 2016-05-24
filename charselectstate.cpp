
#include "charselectstate.h"
#include "playstate.h"
#include <iostream>

CCharSelectState CCharSelectState::CharSelectState;

void CCharSelectState::Init(CGameEngine* game)
{
  std::cout << "CharSelect State started." << std::endl ;
  hero1.play(animations.get(Animations::Human_1_Idle));
  hero1.setLooped(true);
  hero1.setScale(2, 2);
  hero1.setPosition(100, 50);

  hero2.play(animations.get(Animations::Human_10_Idle));
  hero2.setLooped(true);
  hero2.setScale(2, 2);
  hero2.setPosition(200, 50);

  hero3.play(animations.get(Animations::Human_11_Idle));
  hero3.setLooped(true);
  hero3.setScale(2, 2);
  hero3.setPosition(300, 50);

  hero4.play(animations.get(Animations::Human_12_Idle));
  hero4.setLooped(true);
  hero4.setScale(2, 2);
  hero4.setPosition(400, 50);

  hoverBorder.setPosition( hero1.getPosition() );
  selectBorder.setPosition( hero1.getPosition() );

  header.setFont( fonts.get( Fonts::Calibri ) );
  header.setColor( sf::Color::Blue );
  header.setPosition( 50, 150 );
  header.setString( "Select your character by clicking on him. Press SpaceBar to begin." );
}

void CCharSelectState::Cleanup()
{
  std::cout << "CharSelect State ended." << std::endl ;
}

void CCharSelectState::Pause(CGameEngine* game)
{

}

void CCharSelectState::Resume(CGameEngine* game)
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
        if( hero1.getGlobalBounds().contains( static_cast<sf::Vector2f>( sf::Mouse::getPosition( game->window) ) ) )
        {
          std::cout<<"Hero 1 selected"<<std::endl;
          selectBorder.setPosition( hero1.getPosition() );
          selectedHero = 1;
        }
        else if(hero2.getGlobalBounds().contains( static_cast<sf::Vector2f>( sf::Mouse::getPosition( game->window) ) ) )
        {
          std::cout<<"Hero 2 selected"<<std::endl;
          selectBorder.setPosition( hero2.getPosition() );
          selectedHero = 2;
        }
        else if(hero3.getGlobalBounds().contains( static_cast<sf::Vector2f>( sf::Mouse::getPosition( game->window) ) ) )
        {
          std::cout<<"Hero 3 selected"<<std::endl;
          selectBorder.setPosition( hero3.getPosition() );
          selectedHero = 3;
        }
        else if(hero4.getGlobalBounds().contains( static_cast<sf::Vector2f>( sf::Mouse::getPosition( game->window) ) ) )
        {
          std::cout<<"Hero 4 selected"<<std::endl;
          selectBorder.setPosition( hero4.getPosition() );
          selectedHero = 4;
        }
        //game->PushState( CPlayState::Instance() );
        break;
      default:
        //Do Nothing
        break;
    }
  }

    if( hero1.getGlobalBounds().contains( static_cast<sf::Vector2f>( sf::Mouse::getPosition( game->window) ) ) )
    {
      hoverBorder.setPosition( hero1.getPosition() );
    }
    else if(hero2.getGlobalBounds().contains( static_cast<sf::Vector2f>( sf::Mouse::getPosition( game->window) ) ) )
    {
      hoverBorder.setPosition( hero2.getPosition() );
    }
    else if(hero3.getGlobalBounds().contains( static_cast<sf::Vector2f>( sf::Mouse::getPosition( game->window) ) ) )
    {
      hoverBorder.setPosition( hero3.getPosition() );
    }
    else if(hero4.getGlobalBounds().contains( static_cast<sf::Vector2f>( sf::Mouse::getPosition( game->window) ) ) )
    {
      hoverBorder.setPosition( hero4.getPosition() );
    }


}

void CCharSelectState::Update(CGameEngine* game)
{

}

void CCharSelectState::Draw(CGameEngine* game, double interpolation)
{
  game->window.clear( sf::Color::White );

  hero1.update( game->frameTime );
  hero2.update( game->frameTime );
  hero3.update( game->frameTime );
  hero4.update( game->frameTime );

  game->window.draw( header );
  game->window.draw( hoverBorder );
  game->window.draw( selectBorder );
  game->window.draw( hero1 );
  game->window.draw( hero2 );
  game->window.draw( hero3 );
  game->window.draw( hero4 );

  game->window.display();

}
