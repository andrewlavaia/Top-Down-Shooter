
#include "playstate.h"

CPlayState CPlayState::PlayState;

void CPlayState::Init(CGameEngine* game)
{
  std::cout << "Play State started." << std::endl;
  //this->level->Load(1);
  level->background.setTexture( textures.get( Textures::Dungeon ) );
  std::cout << "Level 1 Loaded." << std::endl;
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

  // Movement
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    hero->MoveOneUnit(Orientation::NW, hero->getSpeed());
    hero->setStatus(AnimatedEntity::Moving);
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    hero->MoveOneUnit(Orientation::NE, hero->getSpeed());
    hero->setStatus(AnimatedEntity::Moving);
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    hero->MoveOneUnit(Orientation::SW, hero->getSpeed());
    hero->setStatus(AnimatedEntity::Moving);
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    hero->MoveOneUnit(Orientation::SE, hero->getSpeed());
    hero->setStatus(AnimatedEntity::Moving);
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    hero->MoveOneUnit(Orientation::W, hero->getSpeed());
    hero->setStatus(AnimatedEntity::Moving);
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    hero->MoveOneUnit(Orientation::E, hero->getSpeed());
    hero->setStatus(AnimatedEntity::Moving);
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    hero->MoveOneUnit(Orientation::N, hero->getSpeed());
    hero->setStatus(AnimatedEntity::Moving);
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    hero->MoveOneUnit(Orientation::S, hero->getSpeed());
    hero->setStatus(AnimatedEntity::Moving);
    noKeyPressed = false;
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
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
  {
    hero->PrimaryAttack(this->level->entities);
  }

  // Secondary Attack
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
  {
    hero->SecondaryAttack(this->level->entities);
  }

  // Throw
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    hero->Throw();
  }

/*
  // Spawning Controls (administrative only), requires public member functions
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
  {
    this->level->CreateNPC(NPC::Chumba);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
  {
    this->level->CreateNPC(NPC::Goomba);
  }
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

  // Check if hero reached exit
  for(auto it = this->level->exits.begin(); it != this->level->exits.end(); ++it)
  {
    if(hero->checkCollision(**it))
    {
      std::cout<<"Exit Condition - Push Stack"<<std::endl;
    }
  }

  // Test all other collisions
  for(std::vector< std::shared_ptr<AnimatedEntity> >::iterator it = this->level->entities.begin(); it != this->level->entities.end(); ++it)
  {
    // Set NPC Aggro
    if( (*it)->getParentType() == AnimatedEntity::NPCType
        && (*it)->checkDistance(200, *hero)
        && (  (*it)->getStatus() == AnimatedEntity::Moving
           || (*it)->getStatus() == AnimatedEntity::Idle )
      )
    {
      (*it)->setStatus( AnimatedEntity::Moving );
      (*it)->AddDirection((*it)->getRelativeOrientation(*hero), 0.01, (*it)->getSpeed());
    }

    // Test collision with hero
    hero->collideWithEntity(**it, game->logicTime);

    // Test collision with all other entities
    for(std::vector< std::shared_ptr<AnimatedEntity> >::iterator jt = this->level->entities.begin(); jt != this->level->entities.end(); ++jt)
    {
      (*it)->collideWithEntity(**jt, game->logicTime);
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


  // -------------------
  // Animation Logic
  // -------------------

/*
  for(auto it = level->entities.begin(); it != level->entities.end(); ++it)
  {
    if((*it)->getStatus() == AnimatedEntity::Attacking && !(*it)->animatedSprite.isPlaying()) // if dying with no active die animation, entity should be dead
    {
      (*it)->setStatus(AnimatedEntity::Grabbed);
      (*it)->hitbox.setScale(1,1);
    }
  }
*/


  // -------------------
  // Victory Conditions
  // -------------------
  /*
  if(Victory())
  {
    //push state to victory state
  }

  if(GameOver())
  {
    // push state to game over state
  }
  */

  // -------------------
  // Update HUD
  // -------------------
  HUD_timer.setString(to_string(this->level->getGameOverTime() - this->level->getRunningTime()));
  HUD_npc_count.setString(to_string(this->level->getNPCDeathCount()));
  //update active_weapon image


} // end CState::Update


void CPlayState::Draw(CGameEngine* game, double interpolation)
{

  // Hero Animation Rules
  if(this->noKeyPressed && hero->getStatus() == AnimatedEntity::Moving)
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
    window.setView(view);
  }
  else if( p.x < limit )
  {
    sf::View view = window.getView();
    view.move( hero->getSpeed() * interpolation * -1, 0.0 );
    window.setView(view);
  }
  if( p.y > (double)window.getSize().y - limit )
  {
    sf::View view = window.getView();
    view.move( 0.0, hero->getSpeed() * interpolation );
    window.setView(view);
  }
  else if ( p.y < limit )
  {
    sf::View view = window.getView();
    view.move( 0.0, hero->getSpeed() * interpolation * -1);
    window.setView(view);
  }


  // --------------------
  // Draw Level Background
  // --------------------

  window.draw( level->background );


  // --------------------
  // Draw HUD
  // --------------------
  window.draw(HUD_timer);
  window.draw(HUD_npc_count);
  // draw active weapon image

  // ---------------------
  // Draw Entities
  // ---------------------
  for(std::vector< std::shared_ptr<AnimatedEntity> >::const_iterator it = this->level->entities.begin(); it != this->level->entities.end(); ++it)
  {
    (*it)->animatedSprite.update(game->frameTime);
    (*it)->MoveAnimatedSprite(interpolation);
    window.draw((*it)->animatedSprite);
    //window.draw((*it)->hitbox); // DEBUG only
  }

  // ---------------------
  // Draw Exits - DEBUG ONLY
  // ---------------------
  for(auto it = this->level->exits.begin(); it != this->level->exits.end(); ++it)
  {
    (*it)->animatedSprite.update(game->frameTime);
    (*it)->MoveAnimatedSprite(interpolation);
    window.draw((*it)->animatedSprite);
    window.draw((*it)->hitbox);
  }

  // -------------
  // Draw Hero - drawn last so that it is shown on top of everything
  // -------------
  hero->animatedSprite.update(game->frameTime);
  hero->MoveAnimatedSprite(interpolation);
  window.draw(hero->animatedSprite);
  //window.draw(hero->hitbox); // DEBUG only


  // ---------------
  // Update Window
  // ---------------
  window.display();

}

