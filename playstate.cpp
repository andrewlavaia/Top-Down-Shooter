
#include "playstate.h"

CPlayState CPlayState::PlayState;

void CPlayState::Init(CGameEngine* game)
{
  std::cout << "Play State started." << std::endl;
  level->background.setTexture( textures.get( Textures::Grass ) );

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

  HUD_background.setSize( sf::Vector2f( game->window.getSize().x, game->window.getSize().y * .10 ) );
  crosshair.setPosition( game->window.mapPixelToCoords( sf::Mouse::getPosition( game->window ) ) );
  pause_text.setString("GAME PAUSED");
  game->window.setMouseCursorVisible(false);

}

void CPlayState::Cleanup()
{
  std::cout << "Play State ended." << std::endl;

}

void CPlayState::Pause(CGameEngine* game)
{
    std::cout << "Paused" << std::endl;
    game->isPaused = true;
}

void CPlayState::Resume(CGameEngine* game)
{
    std::cout << "Unpaused" << std::endl;
    game->isPaused = false;
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

  // PAUSE
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) && game->isPaused == false && keyboardReady() )
  {
    Pause(game);
    resetKeyboardCooldown();
  }
  else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) && game->isPaused == true && keyboardReady() )
  {
    Resume(game);
    resetKeyboardCooldown();
  }

  if(!game->isPaused)
  {

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
        // Mouse Controls
    sf::Vector2i heroPos = game->window.mapCoordsToPixel(hero->position);
    float dx = sf::Mouse::getPosition( game->window ).x - heroPos.x; // needs to be negative for cos in tangent function (?)
    float dy = heroPos.y - sf::Mouse::getPosition( game->window ).y;
    const double PI = 3.14159265;
    float rotation = ( atan2( dx, dy ) * 180 )/PI; // take arctangent and convert from radians to degrees
    hero->getWeapon()->animatedSprite.setRotation( rotation );
    hero->getWeapon()->hitbox.setRotation( rotation );

        // Keyboard Controls
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

  } // end if(!isPaused)

  // Reduce Keyboard Input Cooldown
  reduceKeyboardCooldown(game->logicTime);
}


void CPlayState::Update(CGameEngine* game)
{

  game_time += game->logicTime;

  // ---------------
  // Collision Tests
  // ---------------

  // Test all collisions
  for(std::vector< std::shared_ptr<AnimatedEntity> >::iterator it = this->level->entities.begin(); it != this->level->entities.end(); ++it)
  {
    // Test collision with all other entities
    for(std::vector< std::shared_ptr<AnimatedEntity> >::iterator jt = this->level->entities.begin(); jt != this->level->entities.end(); ++jt)
    {
      (*it)->collideWithEntity(**jt, game->logicTime);
    }

    // Test collision with hero
    hero->collideWithEntity(**it, game->logicTime);
  }

  // Trigger NPC aggro
  for( unsigned i = 0; i < level->entities.size(); ++i ) // need to use standard loop otherwise iterators will become invalidated if projectiles are added to entities
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

  // Check if entity should be Dead
  hero->ifDead();
  for( auto it = level->entities.begin(); it != level->entities.end(); ++it )
  {
    (*it)->ifDead();
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

  // Spawn new enemies
  level->spawnNPCs(3, game->logicTime, hero->position);

  // -------------------
  // Game Over Conditions
  // -------------------

  if( hero->getHP() <= 0 )
  {

    game->window.setMouseCursorVisible(true);
    game->window.setView(game->window.getDefaultView());

    level->entities.clear();

    //push state to main menu state
    game->PopState();
    game->PopState();
    game->PopState();


  }


  // -------------------
  // Update HUD
  // -------------------
  HUD_weapon.play( *hero->getWeapon()->getIdleAnimation() );
  HUD_weapon.setRotation( 90 );
  HUD_weapon.pause();
  HUD_health.setString( to_string( hero->getHP() ) );
  HUD_timer.setString( to_string( game_time.asSeconds(), 1 ) );
  HUD_ammo_count.setString( to_string( hero->getWeapon()->getAmmo() ) );
  HUD_sheep_count.setString( to_string( this->level->getEnemyDeathCount() ) );

} // end CState::Update


void CPlayState::Draw(CGameEngine* game, double interpolation)
{

  // Hero Animation Rules
  if( this->noKeyPressed && ( hero->getStatus() == AnimatedEntity::Moving || hero->getStatus() == AnimatedEntity::Impassable ) )
  {
    hero->setStatus(AnimatedEntity::Idle);
    hero->playAnimation();
  }

  // ------------------------
  // Initialize Render Window
  // ------------------------
  sf::RenderWindow& window = game->window;
  window.clear( sf::Color( 0, 0, 0) );

  // Set Views
  sf::View standard = window.getView(); // set current view

  // initialize mini-map view
  unsigned int size = 200; // The 'minimap' view will show a smaller picture of the map
  sf::View minimap(sf::FloatRect(hero->position.x, hero->position.y, static_cast<float>(size), static_cast<float>(window.getSize().y*size/window.getSize().x)));
  minimap.setViewport(sf::FloatRect(0.90f, 0, 0.10f, 0.10f));
  minimap.zoom(10.f);

  sf::RectangleShape miniback; // We want to draw a rectangle behind the minimap
  miniback.setPosition( window.mapPixelToCoords( sf::Vector2i( -1000, -1000 ) ) );
  miniback.setSize(sf::Vector2f(window.getSize().x*10, window.getSize().y*10)); // make background larger than necessary so that it covers entire view
  miniback.setFillColor(sf::Color::White);

  sf::RectangleShape minihero;
  minihero.setPosition(hero->position);
  minihero.setSize(sf::Vector2f(100, 100));
  minihero.setOrigin(50,50);
  minihero.setFillColor(sf::Color::Blue);

  sf::RectangleShape mininpc;
  mininpc.setPosition(sf::Vector2f(-1000,-1000)); // temporary holding place
  mininpc.setSize(sf::Vector2f(80, 80));
  mininpc.setOrigin(40,40);
  mininpc.setFillColor(sf::Color::Red);

  sf::RectangleShape miniweapon;
  miniweapon.setPosition(sf::Vector2f(-1000,-1000)); // temporary holding place
  miniweapon.setSize(sf::Vector2f(40, 40));
  miniweapon.setOrigin(20,20);
  miniweapon.setFillColor(sf::Color::Black);

  // ------------------------
  // Move Camera
  // ------------------------
  // Move view when hero is within 'limit' of  window edge

  sf::Vector2i p = window.mapCoordsToPixel(hero->position);
  const double limit = 200;
  const double max_width = 4000;
  const double max_height = 2658;
  if( p.x > (double)window.getSize().x - limit )
  {
    standard.move( hero->getSpeed()/1.5 * interpolation, 0.0 );
    window.setView( standard );
  }
  else if( p.x < limit )
  {
    standard.move( hero->getSpeed()/1.5 * interpolation * -1, 0.0 );
    window.setView( standard );
  }
  if( p.y > (double)window.getSize().y - limit )
  {
    standard.move( 0.0, hero->getSpeed()/1.5 * interpolation );
    window.setView( standard );
  }
  else if( p.y < limit )
  {
    standard.move( 0.0, hero->getSpeed()/1.5  * interpolation * -1);
    window.setView( standard );
  }


  // --------------------
  // Draw Level Background
  // --------------------

  window.draw( level->background );


  // ---------------------
  // Draw Entities
  // ---------------------
  for(std::vector< std::shared_ptr<AnimatedEntity> >::const_iterator it = this->level->entities.begin(); it != this->level->entities.end(); ++it)
  {
    (*it)->animatedSprite.update(game->frameTime);
    (*it)->MoveAnimatedSprite(interpolation);
    window.draw((*it)->animatedSprite);

    if( (*it)->getParentType() == AnimatedEntity::NPCType )
    {
      if( !(*it)->isDead() )
      {
        window.draw( (*it)->healthbar_damage );
        window.draw( (*it)->healthbar );
      }

      // draw weapon in front of npc only when weapon is not pointing towards top of screen
      if( dynamic_cast<NPC&>(**it).getWeapon()->animatedSprite.getRotation() >= 90
         && dynamic_cast<NPC&>(**it).getWeapon()->animatedSprite.getRotation() <= 270 )
      {
        window.draw( dynamic_cast<NPC&>(**it).getWeapon()->animatedSprite );
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

  // draw weapon in front of hero only when weapon is not pointing towards top of screen
  if( hero->getWeapon()->animatedSprite.getRotation() >= 90
     && hero->getWeapon()->animatedSprite.getRotation() <= 270 )
  {
    window.draw( hero->getWeapon()->animatedSprite );
  }

  // --------------------
  // Draw HUD
  // --------------------
  // move hud to top of active view
  // drawn last so that it is on top of everything
  HUD_background.setPosition( window.mapPixelToCoords( sf::Vector2i( 0, 0 ) ) );
  HUD_health.setPosition( window.mapPixelToCoords( sf::Vector2i( 50, 0 ) ) );
  HUD_weapon.setPosition( window.mapPixelToCoords( sf::Vector2i( 275, 25 ) ) );
  HUD_ammo_count.setPosition (window.mapPixelToCoords( sf::Vector2i( 325, 0 ) ) );
  HUD_timer.setPosition( window.mapPixelToCoords( sf::Vector2i( window.getSize().x/2, 0 ) ) );
  HUD_sheep_count.setPosition( window.mapPixelToCoords( sf::Vector2i( window.getSize().x - 50, 0 ) ) );

  // update AnimatedSprites
  HUD_weapon.update( game->frameTime );

  if( game->isPaused )
  {
    pause_text.setPosition( window.mapPixelToCoords( sf::Vector2i( 250, window.getSize().y/2 - 100 ) ) );
    window.draw( pause_text );
  }


  // draw hud
  window.draw( HUD_background );
  window.draw( HUD_health );
  window.draw( HUD_weapon );
  if( hero->getWeapon()->getAmmo() > 0 )
    window.draw( HUD_ammo_count );
  window.draw( HUD_timer );
  window.draw( HUD_sheep_count );

  // draw minimap
  window.setView( minimap );
  window.draw( miniback );
  for(std::vector< std::shared_ptr<AnimatedEntity> >::const_iterator it = this->level->entities.begin(); it != this->level->entities.end(); ++it)
  {
    if( !(*it)->isDead() && (*it)->getParentType() == AnimatedEntity::NPCType )
    {
      mininpc.setPosition((*it)->position.x, (*it)->position.y);
      mininpc.setFillColor( (*it)->minimap_color );
      window.draw( mininpc );
    } else if( !(*it)->isDead() && (*it)->getParentType() == AnimatedEntity::WeaponType )
    {
      miniweapon.setPosition((*it)->position.x, (*it)->position.y);
      miniweapon.setFillColor( (*it)->minimap_color );
      window.draw( miniweapon );
    }
  }

  window.draw( minihero );
  window.setView( standard );

  // draw crosshair
  crosshair.setPosition( window.mapPixelToCoords( sf::Mouse::getPosition( window ) ) );
  window.draw( crosshair );


  // ---------------
  // Update Window
  // ---------------
  window.display();

}

