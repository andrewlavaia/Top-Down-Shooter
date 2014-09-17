
#include "hero.h"
#include <iostream>

Hero::Hero()
  : weapon( new Weapon(Weapon::Hands) ),
    grabbed_npc(nullptr)
{
  position.x = 50;
  position.y = 50;

  speed = 5;
  strength = 1;

  setOrientation(Orientation::S);

  // set up AnimatedSprite
  animatedSprite.setOrigin(16,16);
  animatedSprite.setPosition(position.x,position.y);

  // set hitbox for collision testing
  sf::Texture hitbox_texture;
  hitbox_texture.create(32,32);
  animatedSprite.hitbox.setTexture(hitbox_texture); // aassign empty texture 20x20 pixels
  animatedSprite.hitbox.setColor(sf::Color(255,0,0,100)); // semi-transparent red hitbox
  animatedSprite.hitbox.setOrigin(16, 16);
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
  this->weapon->sprite.setPosition(this->animatedSprite.getPosition().x, this->animatedSprite.getPosition().y);
}

void Hero::PickupWeapon(std::vector< std::unique_ptr<Weapon> >& weap_vec)
{
   for(std::vector< std::unique_ptr<Weapon> >::iterator it = weap_vec.begin(); it != weap_vec.end(); ++it)
   {
     if(Collision::BoundingBoxTest( (*it)->sprite, this->animatedSprite.hitbox))
     {
       if(weapon->getType() == Weapon::Hands)
       {
         m_weapon_storage = std::move(weapon);
       }
       else
       {
         DropWeapon(weap_vec);
       }

        weapon = std::move(*it);
        it = weap_vec.erase(it);
        std::cout << "Hero picked up the weapon. Now holding weapon type " << weapon->getType() << std::endl;
        weapon->reduceDurability();
        break; // can only pickup one weapon at a time
     }
   }
}

void Hero::DropWeapon(std::vector< std::unique_ptr<Weapon> >& weap_vec)
{
  if(weapon->getType() != Weapon::Hands)
  {

    if (weapon->getDurability() > 0) // else if weapon durability <=0 at time of drop, weapon is destroyed)
    {
      weap_vec.push_back(std::move(weapon));
    }
    else
    {
      std::cout<< "weapon destroyed, durability too low" << std::endl;
    }

    //std::unique_ptr<Weapon> w(new Weapon(Weapon::Hands));
    weapon = std::move(m_weapon_storage);
    std::cout << "Hero dropped the weapon. Now holding weapon type " << weapon->getType() << std::endl;
  }
}

void Hero::PrimaryAttack(std::vector< std::unique_ptr<NPC> >& npc_vec)
{
  if(grabbed_npc == nullptr)
    AttackNPC(this->weapon->getPrimaryAttack(), npc_vec);
}

void Hero::SecondaryAttack(std::vector< std::unique_ptr<NPC> >& npc_vec)
{
  if(grabbed_npc == nullptr)
    AttackNPC(this->weapon->getSecondaryAttack(), npc_vec);
  else
    ThrowNPC(npc_vec);
}

void Hero::AttackNPC( Attack atk, std::vector< std::unique_ptr<NPC> >& npc_vec)
{
  for(std::vector< std::unique_ptr<NPC> >::iterator it = npc_vec.begin(); it != npc_vec.end(); ++it)
  {
    if(Collision::BoundingBoxTest( (*it)->animatedSprite.hitbox, this->animatedSprite.hitbox) )
    {
      switch ( atk.getType() )
      {
        case Attack::Grab :
          std::cout << "NPC grabbed" << std::endl;
          grabbed_npc = std::move(*it);
          it = npc_vec.erase(it);
          grabbed_npc->animatedSprite.stop();
          grabbed_npc->animatedSprite.rotate(90);
          return; // ! necessary otherwise crash when last npc in vector is picked up (can only grab one npc)
          break;

        case Attack::Push :
          std::cout << "NPC pushed" << std::endl;
          (*it)->position.x += strength * (1/(*it)->getWeight()) * ((*it)->position.x - position.x);
          (*it)->position.y += strength * (1/(*it)->getWeight()) * ((*it)->position.y - position.y);
          break;

      }
    }
  }
}

void Hero::ThrowNPC(std::vector< std::unique_ptr<NPC> >& npc_vec)
{
  // set throw animation
  // determine throw direction
  double throw_speed = 20;
  double throw_distance = 100 * ( strength/grabbed_npc->getWeight() );
  grabbed_npc->directions.push_back(Direction(getOrientation(), throw_distance, throw_speed, false));
  grabbed_npc->directions_it = grabbed_npc->directions.end() - 1;
  //collision error when throwing down

  grabbed_npc->animatedSprite.rotate(-90);
  npc_vec.push_back(std::move(grabbed_npc));

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
