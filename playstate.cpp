
#include "playstate.h"
#include "mapmanager.h"
#include "hero.h"
#include "npc.h"
#include "timer.h"
#include "collision.h"


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

  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
  {
    this->level.hero.setOrientation(Orientation::NW);
    this->level.hero.position.x -= this->level.hero.speed;
    this->level.hero.position.y -= this->level.hero.speed;
    this->level.hero.currentAnimation = &this->level.hero.walkAnimationUp;
    noKeyPressed = false;
  }
  else
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
  {
    this->level.hero.setOrientation(Orientation::NE);
    this->level.hero.position.x += this->level.hero.speed;
    this->level.hero.position.y -= this->level.hero.speed;
    this->level.hero.currentAnimation = &this->level.hero.walkAnimationUp;
    noKeyPressed = false;
  }
  else
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
  {
    this->level.hero.setOrientation(Orientation::SW);
    this->level.hero.position.x -= this->level.hero.speed;
    this->level.hero.position.y += this->level.hero.speed;
    this->level.hero.currentAnimation = &this->level.hero.walkAnimationDown;
    noKeyPressed = false;
  }
  else
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
  {
    this->level.hero.setOrientation(Orientation::SE);
    this->level.hero.position.x += this->level.hero.speed;
    this->level.hero.position.y += this->level.hero.speed;
    this->level.hero.currentAnimation = &this->level.hero.walkAnimationDown;
    noKeyPressed = false;
  }
  else
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    this->level.hero.setOrientation(Orientation::W);
    this->level.hero.position.x -= this->level.hero.speed;
    this->level.hero.currentAnimation = &this->level.hero.walkAnimationLeft;
    noKeyPressed = false;
  }
  else
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    this->level.hero.setOrientation(Orientation::E);
    this->level.hero.position.x += this->level.hero.speed;
    this->level.hero.currentAnimation = &this->level.hero.walkAnimationRight;
    noKeyPressed = false;
  }
  else
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    this->level.hero.setOrientation(Orientation::N);
    this->level.hero.position.y -= this->level.hero.speed;
    this->level.hero.currentAnimation = &this->level.hero.walkAnimationUp;
    noKeyPressed = false;
  }
  else
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    this->level.hero.setOrientation(Orientation::S);
    this->level.hero.position.y += this->level.hero.speed;
    this->level.hero.currentAnimation = &this->level.hero.walkAnimationDown;
    noKeyPressed = false;
  }

  // Dodge Left
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    this->level.hero.position.x -= this->level.hero.speed * 3;
    noKeyPressed = false;
  }
  // Dodge Right
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    this->level.hero.position.x += this->level.hero.speed * 3;
    noKeyPressed = false;
  }
  // Dodge Down
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    this->level.hero.position.y += this->level.hero.speed * 3;
    noKeyPressed = false;
  }
  // Dodge Up
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    this->level.hero.position.y -= this->level.hero.speed * 3;
    noKeyPressed = false;
  }

  // Pickup Weapon
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && this->level.hero.grabbed_npc == nullptr ) {
    this->level.hero.PickupWeapon(this->level.weapon);
  }

  // Drop Weapon
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
    this->level.hero.DropWeapon(this->level.weapon);
  }

  // Primary Attack
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
    this->level.hero.PrimaryAttack(this->level.npc);
  }

  // Secondary Attack
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
    this->level.hero.SecondaryAttack(this->level.npc);
  }

  // Spawning Controls
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
    this->level.CreateNPC(NPC::Chumba);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
    this->level.CreateNPC(NPC::Goomba);
  }

  // Load next level
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
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
    // if hero hits any npc (based on hero strength, npc weight, and distance factor)
    if(Collision::BoundingBoxTest(this->level.hero.animatedSprite.hitbox, (*it)->animatedSprite.hitbox))
    {
      // Check if NPC was just thrown
      // NOT IMPLEMENTED YET - Check current animation != throw animation
        double ix = (*it)->position.x;
        double iy = (*it)->position.y;
        double jx = this->level.hero.position.x;
        double jy = this->level.hero.position.y;

        (*it)->position.x += (1/(*it)->getWeight()) * (ix - jx)/2;
        (*it)->position.y += (1/(*it)->getWeight()) * (iy - jy)/2;
    }


    // if any npc runs into another npc (based on weight of each npc)
    for (std::vector< std::unique_ptr<NPC> >::iterator jt = this->level.npc.begin(); jt != this->level.npc.end(); ++jt)
    {
      if(Collision::BoundingBoxTest( (*jt)->animatedSprite.hitbox, (*it)->animatedSprite.hitbox))
      {
        // initialize variables first so that each npc moves back the same distance
        double ix = (*it)->position.x;
        double iy = (*it)->position.y;
        double jx = (*jt)->position.x;
        double jy = (*jt)->position.y;

        (*it)->position.x += (1/(*it)->getWeight()) * (ix - jx)/4;
        (*it)->position.y += (1/(*it)->getWeight()) * (iy - jy)/4;

        (*jt)->position.x += (1/(*jt)->getWeight()) * (jx - ix)/4;
        (*jt)->position.y += (1/(*jt)->getWeight()) * (jy - iy)/4;
      }
    }
  }

  // -------------------
  // Hero Animation
  // -------------------

  this->level.hero.animatedSprite.play(*this->level.hero.currentAnimation);
  if (this->noKeyPressed) { // AND if current animation has completed (not implemented yet)
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


} // end CPlayState::Update


void CPlayState::Draw(CGameEngine* game, double interpolation)
{
  // ---------------
  // Initialize Render Window
  // ---------------

  sf::RenderWindow &window = game->window;
  window.clear(sf::Color(255, 255, 255));

  // -------------
  // Draw Tiles
  // -------------

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
  window.draw(this->level.hero.animatedSprite.hitbox); // debug only


  // ---------------
  // Draw NPCs
  // ---------------

  for (std::vector< std::unique_ptr<NPC> >::const_iterator it = this->level.npc.begin(); it != this->level.npc.end(); ++it)
  {
    (*it)->MoveAnimatedSprite(interpolation);
    window.draw( (*it)->animatedSprite );
    window.draw( (*it)->animatedSprite.hitbox ); // debug only
  }

  if(this->level.hero.grabbed_npc != nullptr)
  {
    this->level.hero.grabbed_npc->MoveAnimatedSprite(interpolation);
    window.draw(this->level.hero.grabbed_npc->animatedSprite);
  }

  // ---------------
  // Draw Weapons
  // ---------------

  //if(this->level.hero.weapon.get() != nullptr) // BUG - arithmetic error on drawing weapon sprite?
  window.draw(this->level.hero.weapon->sprite);

  for (std::vector< std::unique_ptr<Weapon> >::const_iterator it = this->level.weapon.begin(); it != this->level.weapon.end(); ++it)
  {
    window.draw( (*it)->sprite );
  }


  // ---------------
  // Update Window
  // ---------------
  window.display();
}

