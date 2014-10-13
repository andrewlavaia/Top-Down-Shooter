
#include "hero.h"
#include <iostream>

Hero::Hero()
  : weapon( new Weapon(Weapon::Hands) ),
    grabbed_npc(nullptr),
    roped_npc(nullptr)
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
  hitbox_texture.create(20,20);
  animatedSprite.hitbox.setTexture(hitbox_texture); // aassign empty texture 20x20 pixels
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
  this->weapon->sprite.setPosition(this->animatedSprite.getPosition().x, this->animatedSprite.getPosition().y);
}



void Hero::PrimaryAttack(std::vector< std::unique_ptr<NPC> >& npc_vec)
{
  AttackNPC(this->weapon->getPrimaryAttack(),
            this->weapon->getAttackModifier(),
            this->weapon->getRange(),
            npc_vec);
}

void Hero::SecondaryAttack(std::vector< std::unique_ptr<NPC> >& npc_vec)
{
  AttackNPC(this->weapon->getSecondaryAttack(),
        this->weapon->getAttackModifier(),
        this->weapon->getRange(),
        npc_vec);
}


void Hero::Throw(std::vector< std::unique_ptr<NPC> >& npc_vec,
                 std::vector< std::unique_ptr<Weapon> >& weap_vec)
{
  if (roped_npc != nullptr)
  {
    ThrowNPC(npc_vec);
  }
  else
  {
    ThrowNPC(npc_vec);
    ThrowWeapon(weap_vec);
  }
}

void Hero::Pickup(std::vector< std::unique_ptr<NPC> >& npc_vec,
                 std::vector< std::unique_ptr<Weapon> >& weap_vec)
{
  PickupNPC(npc_vec);
  PickupWeapon(weap_vec);
}

void Hero::Drop(std::vector< std::unique_ptr<NPC> >& npc_vec,
                 std::vector< std::unique_ptr<Weapon> >& weap_vec)
{
  if (roped_npc != nullptr)
  {
     DropNPC(npc_vec);
  }
  else
  {
    DropNPC(npc_vec);
    DropWeapon(weap_vec);
  }

}


//-----------------------------
// Private Member Functions
// ----------------------------


void Hero::AttackNPC( Attack atk, double modifier, double rng, std::vector< std::unique_ptr<NPC> >& npc_vec)
{
  // Play Attack Animation
  // Test Collision of animated weapon hitbox instead of hero hitbox? -> NOT IMPLEMENTED YET
  if (grabbed_npc == nullptr && roped_npc == nullptr)
  {
    for(std::vector< std::unique_ptr<NPC> >::iterator it = npc_vec.begin(); it != npc_vec.end(); ++it)
    {
      // Use range attribute of weapon to alter hero's hitbox
      sf::Sprite range_modified_hitbox = this->animatedSprite.hitbox;
      range_modified_hitbox.setOrigin(10,20);
      range_modified_hitbox.scale(1,rng);
      range_modified_hitbox.setRotation(this->getOrientationObj().getRotation());

      if(Collision::BoundingBoxTest( (*it)->animatedSprite.hitbox, range_modified_hitbox) )
      {
        switch ( atk.getType() )
        {
          case Attack::Push :
            std::cout << "NPC pushed" << std::endl;
            (*it)->position.x += modifier * strength * (1/(*it)->getWeight()) * ((*it)->position.x - position.x);
            (*it)->position.y += modifier * strength * (1/(*it)->getWeight()) * ((*it)->position.y - position.y);
            break;

          case Attack::Kick :
            std::cout << "NPC kicked" << std::endl;
            (*it)->position.x += 2 * modifier * strength * (1/(*it)->getWeight()) * ((*it)->position.x - position.x);
            (*it)->position.y += 2 * modifier * strength * (1/(*it)->getWeight()) * ((*it)->position.y - position.y);
            break;

          case Attack::Smash :
            std::cout << "NPC smashed" << std::endl;
            (*it)->position.x += 3 * modifier * strength * (1/(*it)->getWeight()) * ((*it)->position.x - position.x);
            (*it)->position.y += 3 * modifier * strength * (1/(*it)->getWeight()) * ((*it)->position.y - position.y);
            break;

          case Attack::RopeEm :
            std::cout << "NPC roped" << std::endl;
            roped_npc = std::move(*it);
            it = npc_vec.erase(it);
            roped_npc->animatedSprite.stop();
            return; // needed to protect against crash on last npc
            break;

        }
      }
    }
  }
}

void Hero::PickupWeapon(std::vector< std::unique_ptr<Weapon> >& weap_vec)
{
  if (grabbed_npc == nullptr)
  {
    for(std::vector< std::unique_ptr<Weapon> >::iterator it = weap_vec.begin(); it != weap_vec.end(); ++it)
    {
      if(Collision::BoundingBoxTest( (*it)->sprite, animatedSprite.hitbox) )
      {
        DropWeapon(weap_vec);
        m_weapon_storage = std::move(weapon); // store hands weapon, weapon = nullptr
        weapon = std::move(*it);
        it = weap_vec.erase(it);
        weapon->reduceDurability();
        std::cout << "Hero picked up the weapon. Now holding weapon type " << weapon->getType() << std::endl;
        break; // can only pickup one weapon
      }
    }
  }
}

void Hero::DropWeapon(std::vector< std::unique_ptr<Weapon> >& weap_vec)
{
  if(weapon->getType() != Weapon::Hands)
  {
    if (weapon->getDurability() > 0) { // if weapon durability >0 at time of drop, add weaopon back to level
      weap_vec.push_back(std::move(weapon));
    }
    else {
      std::cout<< "weapon destroyed, durability too low" << std::endl;
    }

    // restore hands as active weapon
    weapon = std::move(m_weapon_storage);
    std::cout << "Hero dropped the weapon. Now holding weapon type " << weapon->getType() << std::endl;
  }
}


void Hero::PickupNPC(std::vector< std::unique_ptr<NPC> >& npc_vec)
{
  if (grabbed_npc == nullptr)
  {
    if (weapon->getType() != Weapon::Hands) {
      return;
    }

    for(std::vector< std::unique_ptr<NPC> >::iterator it = npc_vec.begin(); it != npc_vec.end(); ++it)
    {
      if(Collision::BoundingBoxTest( (*it)->animatedSprite.hitbox, this->animatedSprite.hitbox) )
      {
          std::cout << "NPC grabbed" << std::endl;
          grabbed_npc = std::move(*it);
          it = npc_vec.erase(it);
          grabbed_npc->animatedSprite.stop();
          grabbed_npc->animatedSprite.rotate(90);
          return; // ! necessary otherwise crash when last npc in vector is picked up (can only grab one npc)
      }
    }
  }
}

void Hero::DropNPC(std::vector< std::unique_ptr<NPC> >& npc_vec)
{
  if (grabbed_npc != nullptr)
  {
    grabbed_npc->animatedSprite.rotate(-90);
    npc_vec.push_back(std::move(grabbed_npc));
  }

  if (roped_npc != nullptr)
  {
    npc_vec.push_back(std::move(roped_npc));
  }
}

void Hero::ThrowNPC(std::vector< std::unique_ptr<NPC> >& npc_vec)
{
  if (grabbed_npc != nullptr)
  {
    // set throw animation
    double throw_speed = 20;
    double throw_distance = 100 * ( strength/grabbed_npc->getWeight() );
    grabbed_npc->directions.push_back(Direction(getOrientation(), throw_distance, throw_speed, false));
    grabbed_npc->directions.push_back(Direction(getOrientationObj().getOppo(),throw_distance, grabbed_npc->getSpeed(), false)); //npc walks back after thrown
    grabbed_npc->directions_it = grabbed_npc->directions.end() - 2;
    grabbed_npc->distance_travelled = 0;
    // collision ERROR when throwing down
    grabbed_npc->animatedSprite.rotate(-90);
    npc_vec.push_back(std::move(grabbed_npc));
  }
}

void Hero::ThrowWeapon(std::vector< std::unique_ptr<Weapon> >& weap_vec)
{
  if (weapon->getType() != Weapon::Hands)
  {
    // set throw animation
    double throw_speed = 20;
    double throw_distance = 250 * strength;
    weapon->directions.push_back(Direction(getOrientation(), throw_distance, throw_speed, false));
    weapon->directions_it = weapon->directions.end() - 1;

    weap_vec.push_back(std::move(weapon));
    weapon = std::move(m_weapon_storage);
  }
}

