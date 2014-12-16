
#include "hero.h"
#include <iostream>

Hero::Hero()
  : //weapon( new Weapon(Weapon::Hands) ),
    grabbed_npc(nullptr),
    roped_npc(nullptr),
    weapon(nullptr),
    default_weapon(Weapon::Hands)
{
  position.x = 50;
  position.y = 50;

  speed = 10;
  strength = 1;



  // set up AnimatedSprite
  animatedSprite.setOrigin(29,22);
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
  walkAnimation = CreateAnimation(textures.Get(Textures::Hero_Run), 391, 319, 12);
  grabAnimation = CreateAnimation(textures.Get(Textures::Hero_Grab), 388, 319, 6);
  punchAnimation = CreateAnimation(textures.Get(Textures::Hero_Punch), 398, 279, 6);
  kickAnimation = CreateAnimation(textures.Get(Textures::Hero_Kick), 385, 371, 6);

  double scale_factor = 0.10;
  animatedSprite.setScale(scale_factor,scale_factor);

  currentAnimation = &walkAnimation;
  animatedSprite.play(*currentAnimation);
}

// Moves hero sprite -> Overrides AnimatedEntity.MoveAnimatedSprite()
void Hero::MoveAnimatedSprite(double interpolation)
{
  animatedSprite.setOrigin(animatedSprite.getLocalBounds().width/2, animatedSprite.getLocalBounds().height/2);
  sf::Vector2f distance = this->position - this->animatedSprite.getPosition();
  this->animatedSprite.move( distance.x * interpolation, distance.y * interpolation );
  this->animatedSprite.hitbox.setPosition(this->animatedSprite.getPosition().x, this->animatedSprite.getPosition().y);

  if(weapon != nullptr)
    this->weapon->animatedSprite.setPosition(this->animatedSprite.getPosition().x, this->animatedSprite.getPosition().y);
}

void Hero::PrimaryAttack(std::vector< std::shared_ptr<NPC> >& npc_vec)
{
  AttackNPC(this->getWeapon().getPrimaryAttack(),
            this->getWeapon().getAttackModifier(),
            this->getWeapon().getRange(),
            npc_vec);
}

void Hero::SecondaryAttack(std::vector< std::shared_ptr<NPC> >& npc_vec)
{
  AttackNPC(this->getWeapon().getSecondaryAttack(),
        this->getWeapon().getAttackModifier(),
        this->getWeapon().getRange(),
        npc_vec);
}


void Hero::Throw()
{
  if (roped_npc != nullptr)
  {
    ThrowNPC();
  }
  else
  {
    ThrowNPC();
    ThrowWeapon();
  }
}

void Hero::Pickup(std::vector< std::shared_ptr<NPC> >& npc_vec,
                 std::vector< std::shared_ptr<Weapon> >& weap_vec)
{
  PickupNPC(npc_vec);
  PickupWeapon(weap_vec);
}

void Hero::Drop()
{
  if (roped_npc != nullptr)
  {
     DropNPC();
  }
  else
  {
    DropNPC();
    DropWeapon();
  }
}


//-----------------------------
// Private Member Functions
// ----------------------------


void Hero::AttackNPC( Attack atk, double modifier, double rng, std::vector< std::shared_ptr<NPC> >& npc_vec)
{

  // Test Collision of animated weapon hitbox instead of hero hitbox? -> NOT IMPLEMENTED YET
  if (grabbed_npc == nullptr && roped_npc == nullptr)
  {

    // Play Attack Animation
    switch(atk.getType())
    {
      case Attack::Push :
        currentAnimation = &punchAnimation;
        break;

      case Attack::Kick :
        currentAnimation = &kickAnimation;
        break;

      case Attack::Smash :
        currentAnimation = &punchAnimation;
        break;

      case Attack::RopeEm :
        break;
    }


    // Test Collision
    for(std::vector< std::shared_ptr<NPC> >::iterator it = npc_vec.begin(); it != npc_vec.end(); ++it)
    {
      if((*it)->currentAnimation == &(*it)->attackedAnimation)
      {
        break;
      }
      else
      {
        // Use range attribute of weapon to alter hero's hitbox
        sf::Sprite range_modified_hitbox = this->animatedSprite.hitbox;
        range_modified_hitbox.setOrigin(10,20);
        range_modified_hitbox.scale(1,rng);
        range_modified_hitbox.setRotation(this->getOrientation().getRotation());

        if(Collision::BoundingBoxTest( (*it)->animatedSprite.hitbox, range_modified_hitbox) )
        {
          (*it)->currentAnimation = &(*it)->attackedAnimation;
          switch ( atk.getType() )
          {
            case Attack::Push :
              std::cout << "NPC pushed" << std::endl;
              (*it)->Move(getOrientation().getType(), modifier * strength * 20 * (1/(*it)->getWeight()), 10);
              break;

            case Attack::Kick :
              std::cout << "NPC kicked" << std::endl;
              (*it)->Move(getOrientation().getType(), 2 * modifier * strength * 20 * (1/(*it)->getWeight()), 10);
              break;

            case Attack::Smash :
              std::cout << "NPC smashed" << std::endl;
              (*it)->Move(getOrientation().getType(), 3 * modifier * strength * 20 * (1/(*it)->getWeight()), 10);
              break;

            case Attack::RopeEm :
              std::cout << "NPC roped" << std::endl;
              roped_npc = *it;
              roped_npc->animatedSprite.stop();
              break;

          }
        }
      }
    }
  }
}

void Hero::PickupWeapon(std::vector< std::shared_ptr<Weapon> >& weap_vec)
{
  if (grabbed_npc == nullptr)
  {
    currentAnimation = &grabAnimation;
    for(std::vector< std::shared_ptr<Weapon> >::iterator it = weap_vec.begin(); it != weap_vec.end(); ++it)
    {
      if(Collision::BoundingBoxTest( (*it)->animatedSprite.hitbox, animatedSprite.hitbox) )
      {
        DropWeapon();
        weapon = *it;
        weapon->reduceDurability();
        std::cout << "Hero picked up the weapon. Now holding weapon type " << weapon->getType() << std::endl;
        break; // can only pickup one weapon
      }
    }

  }
}

void Hero::DropWeapon()
{
  if(weapon != nullptr)
  {
    weapon = nullptr;
    std::cout << "Hero dropped the weapon." << std::endl;
  }
}

void Hero::ThrowWeapon()
{
  if (weapon != nullptr)
  {
    // set throw animation
    double throw_speed = 20;
    double throw_distance = 250 * strength;
    weapon->Move(getOrientation().getType(), throw_distance, throw_speed);
    //weapon->directions.push_back(Direction(getOrientation().getType(), throw_distance, throw_speed, false));
    //weapon->directions_it = weapon->directions.end() - 1;

    weapon = nullptr;
  }
}

void Hero::PickupNPC(std::vector< std::shared_ptr<NPC> >& npc_vec)
{
  if (grabbed_npc == nullptr)
  {

    if (weapon != nullptr)
    {
      return;
    }

    currentAnimation = &grabAnimation;

    for(std::vector< std::shared_ptr<NPC> >::iterator it = npc_vec.begin(); it != npc_vec.end(); ++it)
    {
      if(Collision::BoundingBoxTest( (*it)->animatedSprite.hitbox, this->animatedSprite.hitbox) )
      {
          std::cout << "NPC grabbed" << std::endl;
          grabbed_npc = *it;
          grabbed_npc->currentAnimation = &grabbed_npc->grabbedAnimation;
          grabbed_npc->animatedSprite.stop();
          grabbed_npc->animatedSprite.rotate(90);
      }
    }
  }
}

void Hero::DropNPC()
{
  if (grabbed_npc != nullptr)
  {
    grabbed_npc->animatedSprite.play();
    grabbed_npc->animatedSprite.rotate(-90);
    grabbed_npc->currentAnimation = &grabbed_npc->defaultAnimation;
    grabbed_npc = nullptr;
  }

  if (roped_npc != nullptr)
  {
    roped_npc->animatedSprite.play();
    roped_npc = nullptr;
  }
}

void Hero::ThrowNPC()
{
  if (grabbed_npc != nullptr)
  {
    grabbed_npc->currentAnimation = &grabbed_npc->thrownAnimation;
    double throw_speed = 20;
    double throw_distance = 100 * ( strength/grabbed_npc->getWeight() );
    grabbed_npc->Move(getOrientation().getType(), throw_distance, throw_speed);
    //grabbed_npc->directions.push_back(Direction(getOrientation().getType(), throw_distance, throw_speed, false));
    //grabbed_npc->directions.push_back(Direction(getOrientation().getOppo(), throw_distance, grabbed_npc->getSpeed(), false)); //npc walks back after thrown
    //grabbed_npc->directions_it = grabbed_npc->directions.end() - 2;
    //grabbed_npc->distance_travelled = 0;
    // collision ERROR when throwing down
    grabbed_npc->animatedSprite.play();
    grabbed_npc->animatedSprite.rotate(-90);
    grabbed_npc = nullptr;
  }
}

Weapon Hero::getWeapon()
{
  if (weapon == nullptr)
    return default_weapon;
  else
    return *weapon;
}
