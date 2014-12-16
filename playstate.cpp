
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

/*
  UP_KEY = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
  DOWN_KEY = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
  LEFT_KEY = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
  RIGHT_KEY = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
*/

  // use pythagorean's theorem to calculate distance when heading NE, NW, SE, or SW
  double hypotenuse = sqrt((this->level.hero.speed * this->level.hero.speed) + (this->level.hero.speed * this->level.hero.speed));

  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
  {
    this->level.hero.setOrientation(Orientation::NW);
    this->level.hero.position.x -= hypotenuse/2;
    this->level.hero.position.y -= hypotenuse/2;
    this->level.hero.animatedSprite.setRotation(315);
    this->level.hero.animatedSprite.play(this->level.hero.walkAnimation);
    noKeyPressed = false;
  }
  else
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
  {
    this->level.hero.setOrientation(Orientation::NE);
    this->level.hero.position.x += hypotenuse/2;
    this->level.hero.position.y -= hypotenuse/2;
    this->level.hero.animatedSprite.setRotation(45);
    this->level.hero.animatedSprite.play(this->level.hero.walkAnimation);
    noKeyPressed = false;
  }
  else
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
  {
    this->level.hero.setOrientation(Orientation::SW);
    this->level.hero.position.x -= hypotenuse/2;
    this->level.hero.position.y += hypotenuse/2;
    this->level.hero.animatedSprite.setRotation(235);
    this->level.hero.animatedSprite.play(this->level.hero.walkAnimation);
    noKeyPressed = false;
  }
  else
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
  {
    this->level.hero.setOrientation(Orientation::SE);
    this->level.hero.position.x += hypotenuse/2;
    this->level.hero.position.y += hypotenuse/2;
    this->level.hero.animatedSprite.setRotation(135);
    this->level.hero.animatedSprite.play(this->level.hero.walkAnimation);
    noKeyPressed = false;
  }
  else
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    this->level.hero.setOrientation(Orientation::W);
    this->level.hero.position.x -= this->level.hero.speed;
    this->level.hero.animatedSprite.setRotation(270);
    this->level.hero.animatedSprite.play(this->level.hero.walkAnimation);
    noKeyPressed = false;
  }
  else
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    this->level.hero.setOrientation(Orientation::E);
    this->level.hero.position.x += this->level.hero.speed;
    this->level.hero.animatedSprite.setRotation(90);
    this->level.hero.animatedSprite.play(this->level.hero.walkAnimation);
    noKeyPressed = false;
  }
  else
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    this->level.hero.setOrientation(Orientation::N);
    this->level.hero.position.y -= this->level.hero.speed;
    this->level.hero.animatedSprite.setRotation(0);
    this->level.hero.animatedSprite.play(this->level.hero.walkAnimation);
    noKeyPressed = false;
  }
  else
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    this->level.hero.setOrientation(Orientation::S);
    this->level.hero.position.y += this->level.hero.speed;
    this->level.hero.animatedSprite.setRotation(180);
    this->level.hero.animatedSprite.play(this->level.hero.walkAnimation);
    noKeyPressed = false;
  }

  // Grab NPC / Pickup Weapon
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
  {
    this->level.hero.Pickup(this->level.npc, this->level.weapons);
    this->level.hero.animatedSprite.play(*this->level.hero.currentAnimation);
  }

  // Release NPC / Drop Weapon
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon))
  {
    this->level.hero.Drop();
  }

  // Primary Attack
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
  {
    this->level.hero.PrimaryAttack(this->level.npc);
    this->level.hero.animatedSprite.play(*this->level.hero.currentAnimation);
  }

  // Secondary Attack
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
  {
    this->level.hero.SecondaryAttack(this->level.npc);
    this->level.hero.animatedSprite.play(*this->level.hero.currentAnimation);
  }

  // Throw
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    this->level.hero.Throw();
  }


  // Spawning Controls
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
    this->level.CreateNPC(NPC::Chumba);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
    this->level.CreateNPC(NPC::Goomba);
  }

  // Load next level
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
    this->level.Load(2);
  }

}

void CPlayState::Update(CGameEngine* game)
{

  // ---------------
  // Collision Tests
  // ---------------

  for (std::vector< std::shared_ptr<NPC> >::iterator it = this->level.npc.begin(); it != this->level.npc.end(); ++it)
  {
    if( (*it)->checkAgroDistance(this->level.hero) && (*it)->currentAnimation == &(*it)->defaultAnimation)
      (*it)->Move((*it)->getRelativeOrientation(this->level.hero), .001, (*it)->getSpeed());

    this->level.CheckCollision_NPCtoHero(it);
    this->level.CheckCollision_NPCtoNPC(it);
    this->level.CheckCollision_NPCtoCollidable(it);
    if (it == this->level.npc.end()) { break; }

  }


  // -------------------
  // NPC AI and Movement
  // -------------------

  this->level.MoveNPCs();
  this->level.MoveWeapons();


  // -------------------
  // Victory Conditions
  // -------------------

  if (this->level.Victory())
  {
    std::cout<<"Victory"<<std::endl;
    //push state to victory state
  }

  if (this->level.GameOver())
  {
    std::cout << "Game Over" <<std::endl;
    // push state to game over state
  }

  // -------------------
  // Update HUD
  // -------------------
  this->level.text_timer.setString(to_string(this->level.getGameOverTime() - this->level.getRunningTime()));
  this->level.text_npc_count.setString(to_string(this->level.getNPCSuccessCount()));
  //update active_weapon image

} // end CPlayState::Update




void CPlayState::Draw(CGameEngine* game, double interpolation)
{

  // ---------------
  // Initialize Render Window
  // ---------------

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

  // -------------------
  // Hero Animation Rules
  // -------------------

  if (this->noKeyPressed && this->level.hero.currentAnimation == &this->level.hero.walkAnimation)
  {
    this->level.hero.animatedSprite.stop();
  }

  if (this->level.hero.currentAnimation != &this->level.hero.walkAnimation && !this->level.hero.animatedSprite.isPlaying())
  {
    this->level.hero.currentAnimation = &this->level.hero.walkAnimation;
  }

  // Update Animation
  this->level.hero.animatedSprite.update(game->frameTime);


  // -------------
  // Draw Hero
  // -------------

  this->level.hero.MoveAnimatedSprite(interpolation);
  window.draw(this->level.hero.animatedSprite);

  // DRAW HIT BOXES FOR DEBUG ONLY
  window.draw(this->level.hero.animatedSprite.hitbox);

  if (this->level.hero.weapon != nullptr)
  {
    float range = this->level.hero.weapon->getRange();
    sf::Sprite range_modified_hitbox = this->level.hero.animatedSprite.hitbox;
    range_modified_hitbox.setOrigin(10,20);
    range_modified_hitbox.scale(1,range);
    range_modified_hitbox.setRotation(this->level.hero.getOrientation().getRotation());
    window.draw(range_modified_hitbox);
  }



  // ---------------
  // Draw NPCs
  // ---------------


  for (std::vector< std::shared_ptr<NPC> >::const_iterator it = this->level.npc.begin(); it != this->level.npc.end(); ++it)
  {
    (*it)->animatedSprite.update(game->frameTime);
    (*it)->MoveAnimatedSprite(interpolation);
    window.draw( (*it)->animatedSprite );
    //window.draw( (*it)->animatedSprite.hitbox ); // debug only

  }

  if(this->level.hero.grabbed_npc != nullptr)
  {
    this->level.hero.grabbed_npc->MoveAnimatedSprite(interpolation);
    window.draw(this->level.hero.grabbed_npc->animatedSprite);
  }

  if(this->level.hero.roped_npc != nullptr)
  {
    this->level.hero.roped_npc->MoveAnimatedSprite(interpolation);
    window.draw(this->level.hero.roped_npc->animatedSprite);
  }

  // ---------------
  // Draw Weapons
  // ---------------


  for (std::vector< std::shared_ptr<Weapon> >::const_iterator it = this->level.weapons.begin(); it != this->level.weapons.end(); ++it)
  {
    (*it)->animatedSprite.update(game->frameTime);
    (*it)->MoveAnimatedSprite(interpolation);
    window.draw( (*it)->animatedSprite );
  }

  // --------------------
  // Draw Collidables
  // --------------------

  for(std::vector< std::unique_ptr<Collidable> >::const_iterator it = this->level.collidables.begin(); it != this->level.collidables.end(); ++it)
  {
    window.draw( (*it)->sprite );
  }

  // ---------------
  // Update Window
  // ---------------
  window.display();



}

