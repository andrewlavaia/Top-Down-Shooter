
#include "playstate.h"
#include "mapmanager.h"
#include "hero.h"
#include "npc.h"
#include "timer.h"
#include "collision.h"
#include <math.h> //sqrt


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
    //this->level.hero.currentAnimation = &this->level.hero.walkAnimationUp;
    noKeyPressed = false;
  }
  else
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
  {
    this->level.hero.setOrientation(Orientation::NE);
    this->level.hero.position.x += hypotenuse/2;
    this->level.hero.position.y -= hypotenuse/2;
    this->level.hero.animatedSprite.setRotation(45);
    //this->level.hero.currentAnimation = &this->level.hero.walkAnimationUp;
    noKeyPressed = false;
  }
  else
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
  {
    this->level.hero.setOrientation(Orientation::SW);
    this->level.hero.position.x -= hypotenuse/2;
    this->level.hero.position.y += hypotenuse/2;
    this->level.hero.animatedSprite.setRotation(235);
    //this->level.hero.currentAnimation = &this->level.hero.walkAnimationDown;
    noKeyPressed = false;
  }
  else
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
  {
    this->level.hero.setOrientation(Orientation::SE);
    this->level.hero.position.x += hypotenuse/2;
    this->level.hero.position.y += hypotenuse/2;
    this->level.hero.animatedSprite.setRotation(135);
    //this->level.hero.currentAnimation = &this->level.hero.walkAnimationDown;
    noKeyPressed = false;
  }
  else
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    this->level.hero.setOrientation(Orientation::W);
    this->level.hero.position.x -= this->level.hero.speed;
    this->level.hero.animatedSprite.setRotation(270);
    //this->level.hero.currentAnimation = &this->level.hero.walkAnimationLeft;
    noKeyPressed = false;
  }
  else
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    this->level.hero.setOrientation(Orientation::E);
    this->level.hero.position.x += this->level.hero.speed;
    this->level.hero.animatedSprite.setRotation(90);
    //this->level.hero.currentAnimation = &this->level.hero.walkAnimationRight;
    noKeyPressed = false;
  }
  else
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    this->level.hero.setOrientation(Orientation::N);
    this->level.hero.position.y -= this->level.hero.speed;
    this->level.hero.animatedSprite.setRotation(0);
    //this->level.hero.currentAnimation = &this->level.hero.walkAnimationUp;
    noKeyPressed = false;
  }
  else
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    this->level.hero.setOrientation(Orientation::S);
    this->level.hero.position.y += this->level.hero.speed;
    this->level.hero.animatedSprite.setRotation(180);
    //this->level.hero.currentAnimation = &this->level.hero.walkAnimationDown;
    noKeyPressed = false;
  }

  // Grab NPC / Pickup Weapon
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
    this->level.hero.Pickup(this->level.npc, this->level.weapon);
  }

  // Release NPC / Drop Weapon
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon)) {
    this->level.hero.Drop(this->level.npc, this->level.weapon);
  }

  // Primary Attack
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
    this->level.hero.PrimaryAttack(this->level.npc);
  }

  // Secondary Attack
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
    this->level.hero.SecondaryAttack(this->level.npc);
  }

  // Throw
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    this->level.hero.Throw(this->level.npc, this->level.weapon);
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
  // Reset Animation Clock
  game->frameTime = game->frameClock.restart();

  // ---------------
  // Collision Tests
  // ---------------

  for (std::vector< std::unique_ptr<NPC> >::iterator it = this->level.npc.begin(); it != this->level.npc.end(); ++it)
  {
    this->level.CheckCollision_NPCtoHero(it);
    this->level.CheckCollision_NPCtoNPC(it);
    this->level.CheckCollision_NPCtoCollidable(it);
    if (it == this->level.npc.end()) { break; }
  }

  // -------------------
  // Hero Animation
  // -------------------

  this->level.hero.animatedSprite.play(*this->level.hero.currentAnimation);
  if (this->noKeyPressed) // AND if current animation has completed (not implemented yet)
  {
    this->level.hero.animatedSprite.stop();
  }
  this->level.hero.animatedSprite.update(game->frameTime);

  // -------------------
  // NPC Animation
  // -------------------

  for (unsigned i = 0; i < this->level.npc.size(); ++i) {
    this->level.npc[i]->animatedSprite.play(*this->level.npc[i]->currentAnimation);
    this->level.npc[i]->animatedSprite.update(game->frameTime);
  }

  /*
  for (std::vector< std::unique_ptr<NPC> >::iterator it = this->level.npc.begin(); it != this->level.npc.end(); ++it) {
    (*it)->animatedSprite.play( (*it)->currentAnimation );
  }
  */

  // -------------------
  // NPC AI and Movement
  // -------------------

  this->level.MoveNPCs();
  this->level.MoveWeapons();


  // -------------------
  // Weapon Movement
  // -------------------




} // end CPlayState::Update


void CPlayState::Draw(CGameEngine* game, double interpolation)
{
  // ---------------
  // Initialize Render Window
  // ---------------

  sf::RenderWindow &window = game->window;
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


  // -------------
  // Draw Hero
  // -------------

  this->level.hero.MoveAnimatedSprite(interpolation);
  window.draw(this->level.hero.animatedSprite);

  // DRAW HIT BOXES FOR DEBUG ONLY
  window.draw(this->level.hero.animatedSprite.hitbox);

  float range = this->level.hero.weapon->getRange();
  sf::Sprite range_modified_hitbox = this->level.hero.animatedSprite.hitbox;
  range_modified_hitbox.setOrigin(10,20);
  range_modified_hitbox.scale(1,range);
  range_modified_hitbox.setRotation(this->level.hero.getOrientationObj().getRotation());
  window.draw(range_modified_hitbox);


  // ---------------
  // Draw NPCs
  // ---------------

  for (std::vector< std::unique_ptr<NPC> >::const_iterator it = this->level.npc.begin(); it != this->level.npc.end(); ++it)
  {
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

  //if(this->level.hero.weapon.get() != nullptr) // BUG - arithmetic error on drawing weapon sprite?
  //window.draw(this->level.hero.weapon->sprite);

  for (std::vector< std::unique_ptr<Weapon> >::const_iterator it = this->level.weapon.begin(); it != this->level.weapon.end(); ++it)
  {
    (*it)->MoveSprite(interpolation);
    window.draw( (*it)->sprite );
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

