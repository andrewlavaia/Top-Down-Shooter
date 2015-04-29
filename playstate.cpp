
#include "playstate.h"
#include "mapmanager.h"
#include "hero.h"
#include "npc.h"
#include "timer.h"
#include "collision.h"
#include <math.h> // sqrt
#include "helpers.h" // to_string


CPlayState CPlayState::PlayState;

void CPlayState::Init()
{
  std::cout << "Play State started." << std::endl;
  //this->level->Load(1);
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

  // Rest if hero reached exit
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
    if(typeid(**it) == typeid(NPC) &&
       (*it)->checkDistance(200, *hero) &&
       (*it)->animatedSprite.isPlaying() &&
       (*it)->getStatus() == AnimatedEntity::Moving
      )
    {
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
  // Reduce Cool Downs
  // -------------------

  hero->getWeapon()->primaryAttack->reduceCooldown(game->logicTime);
  hero->getWeapon()->secondaryAttack->reduceCooldown(game->logicTime);

  // obsolete
  /*
  hero->reduceCoolDowns(game->logicTime);
  if(hero->getWeapon()->getType() == Weapon::Hands)
    hero->getWeapon()->reduceCoolDowns(game->logicTime);

  for(auto it = this->level->entities.begin(); it != this->level->entities.end(); ++it)
  {
    (*it)->reduceCoolDowns(game->logicTime);
  }
  */

  // -------------------
  // NPC AI and Movement
  // -------------------
  level->MoveEntities();
  hero->MoveGrabbedEntities();

  // -------------------
  // Animation Logic
  // -------------------

/*
  if(!hero->animatedSprite.isPlaying() && hero->getStatus() != AnimatedEntity::Dead)
  {
    hero->setStatus(AnimatedEntity::Idle);
  }

  for(auto it = level->entities.begin(); it != level->entities.end(); ++it)
  {
    if(!(*it)->animatedSprite.isPlaying() && (*it)->getStatus() != AnimatedEntity::Dead)
      (*it)->setStatus(AnimatedEntity::Idle);
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
  // --------------------------------------------
  // Game logic dependent on current render state
  // ---------------------------------------------

  // Below code must be in render section, because it depends on current animation state

  // Delete Dead entities
  this->level->DeleteEntities();

  // Hero Animation Rules
  if(this->noKeyPressed && hero->getStatus() == AnimatedEntity::Moving)
    hero->setStatus(AnimatedEntity::Idle);

  if(!hero->animatedSprite.isPlaying()) //&& hero->getCurrentAnimation() != hero->moveAnimation)
  {
    hero->restoreDefaultState();
  }

  // ------------------------
  // Initialize Render Window
  // ------------------------
  sf::RenderWindow& window = game->window;
  window.clear(sf::Color(255, 255, 255));


  // --------------------
  // Draw Map
  // --------------------

  // note: copying the tilemap initially is much quicker than using the member function calls in loop
  std::vector<std::vector<Tile>> tilemap = this->level->mp.GetTiles();
  for(unsigned i = 0; i < tilemap.size(); i++)
  {
    for(unsigned j = 0; j < tilemap[i].size(); j++)
    {
      window.draw(tilemap[i][j].sprite);
    }
  }

  // --------------------
  // Draw HUD
  // --------------------
  window.draw(HUD_timer);
  window.draw(HUD_npc_count);
  // draw active weapon image


  // -------------
  // Draw Hero
  // -------------
  //hero->animatedSprite.play(*hero->getCurrentAnimation());
  hero->playAnimation();
  hero->animatedSprite.update(game->frameTime);
  hero->MoveAnimatedSprite(interpolation);
  window.draw(hero->animatedSprite);
  //window.draw(hero->animatedSprite.hitbox); // DEBUG only

  // ---------------------
  // Draw Entities
  // ---------------------
  for(std::vector< std::shared_ptr<AnimatedEntity> >::const_iterator it = this->level->entities.begin(); it != this->level->entities.end(); ++it)
  {
    //(*it)->animatedSprite.play(*(*it)->getCurrentAnimation());
    (*it)->playAnimation();
    (*it)->animatedSprite.update(game->frameTime);
    (*it)->MoveAnimatedSprite(interpolation);
    window.draw((*it)->animatedSprite);
    //window.draw((*it)->animatedSprite.hitbox); // DEBUG only
  }

  // ---------------------
  // Draw Exits - DEBUG ONLY
  // ---------------------
  for(auto it = this->level->exits.begin(); it != this->level->exits.end(); ++it)
  {
    //(*it)->animatedSprite.play(*(*it)->getCurrentAnimation());
    (*it)->playAnimation();
    (*it)->animatedSprite.update(game->frameTime);
    (*it)->MoveAnimatedSprite(interpolation);
    window.draw((*it)->animatedSprite);
    //window.draw((*it)->animatedSprite.hitbox);
  }


  // ---------------
  // Update Window
  // ---------------
  window.display();


}

