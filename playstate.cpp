
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
  this->level.Load(1);
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
    this->level.hero.MoveOneUnit(Orientation::NW, this->level.hero.getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    this->level.hero.MoveOneUnit(Orientation::NE, this->level.hero.getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    this->level.hero.MoveOneUnit(Orientation::SW, this->level.hero.getSpeed());
    noKeyPressed = false;
  }
  else
  if( sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    this->level.hero.MoveOneUnit(Orientation::SE, this->level.hero.getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    this->level.hero.MoveOneUnit(Orientation::W, this->level.hero.getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    this->level.hero.MoveOneUnit(Orientation::E, this->level.hero.getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    this->level.hero.MoveOneUnit(Orientation::N, this->level.hero.getSpeed());
    noKeyPressed = false;
  }
  else
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    this->level.hero.MoveOneUnit(Orientation::S, this->level.hero.getSpeed());
    noKeyPressed = false;
  }

  // Pickup NPC or Weapon
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
  {
    this->level.hero.Pickup(this->level.entities);
  }

  // Drop NPC or Weapon
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon))
  {
    this->level.hero.Drop();
  }

  // Primary Attack
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::K) && this->level.hero.getWeapon()->primaryAttack->canAttack())
  {
    this->level.hero.PrimaryAttack(this->level.entities);
  }

  // Secondary Attack
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::L) && this->level.hero.getWeapon()->secondaryAttack->canAttack())
  {
    this->level.hero.SecondaryAttack(this->level.entities);
  }

  // Throw
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    this->level.hero.Throw();
  }

  // Spawning Controls (administrative only)
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
  {
    this->level.CreateNPC(NPC::Chumba);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
  {
    this->level.CreateNPC(NPC::Goomba);
  }

  // Shoot Projectile
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
  {
    this->level.CreateProjectile( Projectile::Bullet,
                                  this->level.hero.position.x,
                                  this->level.hero.position.y,
                                  this->level.hero.getOrientation().getType());
  }

  // Load next level
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
    this->level.Load(2);
  }

}


void CPlayState::Update(CGameEngine* game)
{

  // ---------------
  // Collision Tests
  // ---------------
  for (std::vector< std::shared_ptr<AnimatedEntity> >::iterator it = this->level.entities.begin(); it != this->level.entities.end(); ++it)
  {
    // Set NPC Aggro
    if(typeid(**it) == typeid(NPC) &&
        (*it)->checkDistance(200, this->level.hero) &&
        (*it)->getCurrentAnimation() == (*it)->moveAnimation
      )
    {
      (*it)->AddDirection((*it)->getRelativeOrientation(this->level.hero), .25, (*it)->getSpeed());
    }

    // Test collision with hero
    this->level.hero.collideWithEntity(**it, game->logicTime);

    // Test collision with all other entities
    for(std::vector< std::shared_ptr<AnimatedEntity> >::iterator jt = this->level.entities.begin(); jt != this->level.entities.end(); ++jt)
    {
      (*it)->collideWithEntity(**jt, game->logicTime);
    }
  }

  // -------------------
  // Reduce Cool Downs
  // -------------------

  this->level.hero.getWeapon()->primaryAttack->reduceCooldown(game->logicTime);
  this->level.hero.getWeapon()->secondaryAttack->reduceCooldown(game->logicTime);

  // obsolete
  /*
  this->level.hero.reduceCoolDowns(game->logicTime);
  if(this->level.hero.getWeapon()->getType() == Weapon::Hands)
    this->level.hero.getWeapon()->reduceCoolDowns(game->logicTime);

  for(auto it = this->level.entities.begin(); it != this->level.entities.end(); ++it)
  {
    (*it)->reduceCoolDowns(game->logicTime);
  }
  */

  // -------------------
  // NPC AI and Movement
  // -------------------
  this->level.MoveEntities();

  // -------------------
  // Victory Conditions
  // -------------------
  if(this->level.Victory())
  {
    //push state to victory state
  }

  if(this->level.GameOver())
  {
    // push state to game over state
  }

  // -------------------
  // Update HUD
  // -------------------
  this->level.text_timer.setString(to_string(this->level.getGameOverTime() - this->level.getRunningTime()));
  this->level.text_npc_count.setString(to_string(this->level.getNPCSuccessCount()));
  //update active_weapon image


} // end CState::Update


void CPlayState::Draw(CGameEngine* game, double interpolation)
{
  /// Below code must be in render section, because it depends on current animation state

    // Delete destroyed entities
    this->level.DeleteEntities();

    // -------------------
    // Hero Animation Rules
    // -------------------
    if(this->noKeyPressed && this->level.hero.getCurrentAnimation() == this->level.hero.moveAnimation)
      this->level.hero.animatedSprite.stop();

    if(!this->level.hero.animatedSprite.isPlaying()) //&& this->level.hero.getCurrentAnimation() != this->level.hero.moveAnimation)
    {
      this->level.hero.restoreDefaultState();
    }

  /// End

  // ------------------------
  // Initialize Render Window
  // ------------------------
  sf::RenderWindow& window = game->window;
  window.clear(sf::Color(255, 255, 255));


  // --------------------
  // Draw Map
  // --------------------

  // note: copying the tilemap initially is much quicker than using the member function calls in loop
  std::vector<std::vector<Tile>> tilemap = this->level.mp.GetTiles();
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
  window.draw(this->level.text_timer);
  window.draw(this->level.text_npc_count);
  // draw active weapon image


  // -------------
  // Draw Hero
  // -------------
  this->level.hero.animatedSprite.play(*this->level.hero.getCurrentAnimation());
  this->level.hero.animatedSprite.update(game->frameTime);
  this->level.hero.MoveAnimatedSprite(interpolation);
  window.draw(this->level.hero.animatedSprite);
  window.draw(this->level.hero.animatedSprite.hitbox); // DEBUG only

  // ---------------------
  // Draw Entities
  // ---------------------
  for(std::vector< std::shared_ptr<AnimatedEntity> >::const_iterator it = this->level.entities.begin(); it != this->level.entities.end(); ++it)
  {
    (*it)->animatedSprite.play(*(*it)->getCurrentAnimation());
    (*it)->animatedSprite.update(game->frameTime);
    (*it)->MoveAnimatedSprite(interpolation);
    window.draw((*it)->animatedSprite);
    window.draw((*it)->animatedSprite.hitbox); // DEBUG only
  }

  // ---------------
  // Update Window
  // ---------------
  window.display();


}

