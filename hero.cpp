
#include "hero.h"
#include <iostream>

Hero::Hero()
  : weapon( new Weapon(Weapon::Hands) )
{
  position.x = 50;
  position.y = 50;

  speed = 5;
  strength = 5;

}

void Hero::CreateAnimatedSprite()
{
  animatedSprite.setOrigin(16,16);
  animatedSprite.setPosition(position.x,position.y);

  // set hitbox for collision testing
  sf::Texture texture;
  texture.create(20,20);
  animatedSprite.hitbox.setTexture(texture); // aassign empty texture 20x20 pixels
  animatedSprite.hitbox.setColor(sf::Color(255,0,0,100)); // semi-transparent red hitbox
  animatedSprite.hitbox.setOrigin(10, 10);
  animatedSprite.hitbox.setPosition(position.x,position.y);

}

void Hero::CreateAnimations(const TextureManager& textures)
{
  walkAnimationDown.setSpriteSheet(textures.Get(Textures::Hero));
  walkAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
  walkAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
  walkAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
  walkAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

  walkAnimationLeft.setSpriteSheet(textures.Get(Textures::Hero));
  walkAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
  walkAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
  walkAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
  walkAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

  walkAnimationRight.setSpriteSheet(textures.Get(Textures::Hero));
  walkAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
  walkAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
  walkAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
  walkAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

  walkAnimationUp.setSpriteSheet(textures.Get(Textures::Hero));
  walkAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
  walkAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
  walkAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
  walkAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

  currentAnimation = &walkAnimationRight;

}

// Moves hero sprite
void Hero::MoveAnimatedSprite(double interpolation)
{
  sf::Vector2f distance = this->position - this->animatedSprite.getPosition();
  this->animatedSprite.move( distance.x * interpolation, distance.y * interpolation );
  this->animatedSprite.hitbox.setPosition(this->animatedSprite.getPosition().x, this->animatedSprite.getPosition().y);
}

void Hero::PickupWeapon(std::vector< std::unique_ptr<Weapon> >& v)
{
   for(std::vector< std::unique_ptr<Weapon> >::iterator it = v.begin(); it != v.end(); ++it)
   {
      if( (*it)->getType() == Weapon::Lasso ) // if collision with weapon
      {
        DropWeapon(v);
        weapon = std::move(*it);
        it = v.erase(it);
        std::cout << "Hero picked up the weapon. Now holding weapon type " << weapon->getType() << std::endl;
        weapon->reduceDurability();
        break; // can only pickup one weapon at a time
      }
   }
}

void Hero::DropWeapon(std::vector< std::unique_ptr<Weapon> >& v)
{
  if(weapon->getType() != Weapon::Hands) // AND DURABILITY != 0, not implemented yet
  {
    if (weapon->getDurability() > 0) // if weapon durability <=0 at time of drop, weapon is destroyed)
    {
      v.push_back(std::move(weapon));
    }
    else
    {
      std::cout<< "weapon destroyed, durability too low" << std::endl;
    }

    std::unique_ptr<Weapon> w(new Weapon(Weapon::Hands));
    weapon = std::move(w);
    std::cout << "Hero dropped the weapon. Now holding weapon type " << weapon->getType() << std::endl;
  }
}


/*
// Dynamically creates a new Weapon object and returns a smart pointer to it
std::unique_ptr<Weapon> Hero::CreateWeapon(Weapon::Type type)
{
  std::unique_ptr<Weapon> p_weapon( new Weapon(type) );
  return p_weapon;
}

void Hero::DropWeapon ()
{
  std::unique_ptr<Weapon> temp = Hero::CreateWeapon(Weapon::Hands);
  weapon = std::move(temp);
}

void Hero::PickupWeapon(std::unique_ptr<Weapon>& weap)
{
  //std::cout << weapon->getType() << std::endl;
  weapon = std::move(weap);
  //std::cout << weapon->getType() << std::endl;
}
*/
