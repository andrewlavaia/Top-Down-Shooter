
#include "playstate.h"

CPlayState CPlayState::PlayState;

void CPlayState::Init(CGameEngine* game)
{
  std::cout << "Play State started." << std::endl;
  //this->level->Load(1);
  level->background.setTexture( textures.get( Textures::Dungeon ) );
  std::cout << "Level 1 Loaded." << std::endl;
  std::cout<< "Hero " << CCharSelectState::Instance()->getSelectedHero() << " selected" << std::endl;

  switch( CCharSelectState::Instance()->getSelectedHero() )
 {
  case 1:
    hero = std::make_shared<Hero>(Hero::Bob, animations, data);
    break;

  case 2:
    hero = std::make_shared<Hero>(Hero::SuitDrew, animations, data);
    break;

  case 3:
    hero = std::make_shared<Hero>(Hero::GeezerHarry, animations, data);
    break;

  case 4:
    hero = std::make_shared<Hero>(Hero::DirtyPete, animations, data);
    break;

  default:
    break;
 }

  HUD_background.setSize( sf::Vector2f( game->window.getSize().x, 50 ) );
}

void CPlayState::Cleanup()
{
  std::cout << "Play State ended." << std::endl;
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
  this->noKeyPressed = true;

  // ---------------
  // Window Events
  // ---------------
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

  // -----------------
  // Keyboard Events
  // -----------------

  // Hero Movement
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && hero->getStatus() != AnimatedEntity::Impassable )
  {
    hero->setStatus(AnimatedEntity::Moving);
    hero->setOrientation(Orientation::NW);
    hero->MoveOneUnit(Orientation::NW, hero->getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && hero->getStatus() != AnimatedEntity::Impassable )
  {
    hero->setStatus(AnimatedEntity::Moving);
    hero->setOrientation(Orientation::NE);
    hero->MoveOneUnit(Orientation::NE, hero->getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && hero->getStatus() != AnimatedEntity::Impassable )
  {
    hero->setStatus(AnimatedEntity::Moving);
    hero->setOrientation(Orientation::SW);
    hero->MoveOneUnit(Orientation::SW, hero->getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && hero->getStatus() != AnimatedEntity::Impassable )
  {
    hero->setStatus(AnimatedEntity::Moving);
    hero->setOrientation(Orientation::SE);
    hero->MoveOneUnit(Orientation::SE, hero->getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && hero->getStatus() != AnimatedEntity::Impassable )
  {
    hero->setStatus(AnimatedEntity::Moving);
    hero->setOrientation(Orientation::W);
    hero->MoveOneUnit(Orientation::W, hero->getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && hero->getStatus() != AnimatedEntity::Impassable )
  {
    hero->setStatus(AnimatedEntity::Moving);
    hero->setOrientation(Orientation::E);
    hero->MoveOneUnit(Orientation::E, hero->getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && hero->getStatus() != AnimatedEntity::Impassable )
  {
    hero->setStatus(AnimatedEntity::Moving);
    hero->setOrientation(Orientation::N);
    hero->MoveOneUnit(Orientation::N, hero->getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && hero->getStatus() != AnimatedEntity::Impassable )
  {
    hero->setStatus(AnimatedEntity::Moving);
    hero->setOrientation(Orientation::S);
    hero->MoveOneUnit(Orientation::S, hero->getSpeed());
    noKeyPressed = false;
  }

  // Weapon Rotation
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
  {
    hero->getWeapon()->animatedSprite.rotate( 3 );
    hero->getWeapon()->hitbox.rotate( 3 );
  }
  else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
  {
    hero->getWeapon()->animatedSprite.rotate( -3 );
    hero->getWeapon()->hitbox.rotate( -3 );
  }


  // Pickup NPC or Weapon
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
  {
    hero->Pickup(this->level->entities);
  }

  // Drop NPC or Weapon
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon))
  {
    hero->Drop();
  }

  // Primary Attack
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::K ) || sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
  {
    hero->PrimaryAttack( this->level->entities );
  }

  // Secondary Attack
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::L ) || sf::Mouse::isButtonPressed( sf::Mouse::Right ) )
  {
    hero->SecondaryAttack( this->level->entities );
  }

  // Throw
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
  {
    hero->Throw();
  }


  // Spawning Controls (administrative only), requires public member functions
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num1 ) )
  {
    this->level->CreateNPC( NPC::BigRick, rand() % (int)level->getBounds().x, rand() % (int)level->getBounds().y );
  }

  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num2 ) )
  {
    this->level->CreateNPC( NPC::McGinger, rand() % (int)level->getBounds().x, rand() % (int)level->getBounds().y  );
  }

  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num3 ) )
  {
    this->level->CreateNPC( NPC::Sheep, rand() % (int)level->getBounds().x, rand() % (int)level->getBounds().y  );
  }
/*
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
  {
    this->level->CreateProjectile( Projectile::Bullet,
                                  hero->position.x,
                                  hero->position.y,
                                  hero->getOrientation().getType());
  }
*/


  // Load next level
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
    //this->level->Load(2);
  }

}


void CPlayState::Update(CGameEngine* game)
{

  // ---------------
  // Collision Tests
  // ---------------

  // Test all collisions
  for(std::vector< std::shared_ptr<AnimatedEntity> >::iterator it = this->level->entities.begin(); it != this->level->entities.end(); ++it)
  {

    // Test collision with hero
    hero->collideWithEntity(**it, game->logicTime);

    // Test collision with all other entities
    for(std::vector< std::shared_ptr<AnimatedEntity> >::iterator jt = this->level->entities.begin(); jt != this->level->entities.end(); ++jt)
    {
      (*it)->collideWithEntity(**jt, game->logicTime);
    }

  }

  // Trigger NPC aggro
  for( auto i = 0; i < level->entities.size(); ++i ) // need to use standard loop otherwise iterators will become invalidated if projectiles are added to entities
  {
    if( level->entities[i]->getParentType() == AnimatedEntity::NPCType )
    {
      dynamic_cast<NPC&>(*level->entities[i]).engageHero(*hero, *level);
    }
  }

  // -------------------
  // Move Entities
  // -------------------
  level->MoveEntities(); // having this after collision detection helps delete dead entities quicker
  hero->MoveGrabbedEntities();

  // -------------------
  // Cleanup Dead Entities
  // -------------------

  // Check if hero should be Dead
  if(hero->getStatus() == AnimatedEntity::Die && !hero->animatedSprite.isPlaying()) // if dying with no active die animation, entity should be dead
  {
    hero->setStatus(AnimatedEntity::Dead);
    hero->playAnimation();
  }

  // Check if entity should be Dead
  for(auto it = level->entities.begin(); it != level->entities.end(); ++it)
  {
    if((*it)->getStatus() == AnimatedEntity::Die && !(*it)->animatedSprite.isPlaying()) // if dying with no active die animation, entity should be dead
    {
      (*it)->setStatus(AnimatedEntity::Dead);
      (*it)->playAnimation();
    }
  }

  // remove dead entities from level
  level->DeleteEntities();

  // -------------------
  // Reduce Cool Downs
  // -------------------

  hero->getWeapon()->primaryAttack->reduceCooldown(game->logicTime);
  hero->getWeapon()->secondaryAttack->reduceCooldown(game->logicTime);

  //hero->reduceCollisionCooldown( game->logicTime );
  for( auto it = level->entities.begin(); it != level->entities.end(); ++it )
  {
    if( (*it)->getParentType() == AnimatedEntity::NPCType )
    {
      dynamic_cast<NPC&>(**it).getWeapon()->primaryAttack->reduceCooldown(game->logicTime);
      dynamic_cast<NPC&>(**it).getWeapon()->secondaryAttack->reduceCooldown(game->logicTime);
    }
  }


  // -------------------
  // Victory Conditions
  // -------------------
  /*
  if( Victory() )
  {
    //push state to victory state
  }

  if( GameOver() )
  {
    // push state to game over state
  }
  */

  // -------------------
  // Update HUD
  // -------------------
  HUD_weapon.play( *hero->getWeapon()->animatedSprite.getAnimation() );
  HUD_weapon.setLooped( true );
  HUD_weapon.setRotation( 90 );
  HUD_health.setString( to_string( hero->getHP() ) );
  HUD_timer.setString( to_string( this->level->getGameOverTime() - this->level->getRunningTime() ) );
  HUD_sheep_count.setString( to_string( this->level->getNPCDeathCount() ) );

} // end CState::Update


void CPlayState::Draw(CGameEngine* game, double interpolation)
{

  // Hero Animation Rules
  if(this->noKeyPressed && ( hero->getStatus() == AnimatedEntity::Moving || hero->getStatus() == AnimatedEntity::Impassable ) )
  {
    hero->setStatus(AnimatedEntity::Idle);
    hero->playAnimation();
  }

  // ------------------------
  // Initialize Render Window
  // ------------------------
  sf::RenderWindow& window = game->window;
  window.clear( sf::Color( 0, 0, 0) );

  // ------------------------
  // Move Camera
  // ------------------------
  // Move view when hero is within 'limit' of  window edge

  //std::cout << hero->position.x << ", " <<hero->position.y << std::endl;

  sf::Vector2i p = window.mapCoordsToPixel(hero->position);
  const double limit = 200;
  if( p.x > (double)window.getSize().x - limit )
  {
    sf::View view = window.getView();
    view.move( hero->getSpeed() * interpolation, 0.0 );
    window.setView( view );
  }
  else if( p.x < limit )
  {
    sf::View view = window.getView();
    view.move( hero->getSpeed() * interpolation * -1, 0.0 );
    window.setView( view );
  }
  if( p.y > (double)window.getSize().y - limit )
  {
    sf::View view = window.getView();
    view.move( 0.0, hero->getSpeed() * interpolation );
    window.setView( view );
  }
  else if( p.y < limit )
  {
    sf::View view = window.getView();
    view.move( 0.0, hero->getSpeed() * interpolation * -1);
    window.setView( view );
  }


  // --------------------
  // Draw Level Background
  // --------------------

  window.draw( level->background );

  // --------------------
  // Draw HUD
  // --------------------
  // move hud to top of active view
  HUD_background.setPosition( window.mapPixelToCoords( sf::Vector2i( 0, 0 ) ) );
  HUD_health.setPosition( window.mapPixelToCoords( sf::Vector2i( 50, 0 ) ) );
  HUD_weapon.setPosition( window.mapPixelToCoords( sf::Vector2i( 150, 10 ) ) );
  HUD_timer.setPosition( window.mapPixelToCoords( sf::Vector2i( window.getSize().x/2, 0 ) ) );
  HUD_sheep_count.setPosition( window.mapPixelToCoords( sf::Vector2i( window.getSize().x - 50, 0 ) ) );

  // update AnimatedSprites
  HUD_weapon.update( game->frameTime );

  // draw hud
  window.draw( HUD_background );
  window.draw( HUD_health );
  window.draw( HUD_weapon );
  window.draw( HUD_timer );
  window.draw( HUD_sheep_count );

  // ---------------------
  // Draw Entities
  // ---------------------
  for(std::vector< std::shared_ptr<AnimatedEntity> >::const_iterator it = this->level->entities.begin(); it != this->level->entities.end(); ++it)
  {
    (*it)->animatedSprite.update(game->frameTime);
    (*it)->MoveAnimatedSprite(interpolation);
    window.draw((*it)->animatedSprite);
    //window.draw((*it)->hitbox); // DEBUG only
    if( (*it)->getParentType() == AnimatedEntity::NPCType )
    {
      if( !(*it)->isDead() )
      {
        window.draw( (*it)->healthbar_damage );
        window.draw( (*it)->healthbar );
      }

      if( dynamic_cast<NPC&>(**it).getWeapon() != nullptr )
      {
        NPC& npc = dynamic_cast<NPC&>(**it);
        npc.getWeapon()->animatedSprite.update( game->frameTime );
        npc.getWeapon()->MoveAnimatedSprite( interpolation );
        window.draw( npc.getWeapon()->animatedSprite );
      }
    }

  }

  // -------------
  // Draw Hero
  // -------------
  // drawn last so that Hero is shown on top of everything
  hero->animatedSprite.update( game->frameTime );
  hero->MoveAnimatedSprite( interpolation );
  window.draw( hero->animatedSprite );
  //window.draw(hero->hitbox); // DEBUG only

  // draw weapon in front of hero only when weapon is not pointing towards top of screen
  if( hero->getWeapon()->animatedSprite.getRotation() >= 90
     && hero->getWeapon()->animatedSprite.getRotation() <= 270 )
  {
    window.draw( hero->getWeapon()->animatedSprite );
  }



  // ---------------
  // Update Window
  // ---------------
  window.display();

}

