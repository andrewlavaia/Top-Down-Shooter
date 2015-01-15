
#include "hero.h"
#include <iostream>

Hero::Hero()
  : grabbed_npc(nullptr),
    weapon(nullptr),
    default_weapon(new Weapon(Weapon::Hands, 50, 50))
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
  animatedSprite.hitbox.setTexture(hitbox_texture); // assign empty texture 20x20 pixels
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

  setCurrentAnimation(walkAnimation);
  animatedSprite.play(*getCurrentAnimation());
}

void Hero::collideWithEntity(const AnimatedEntity& a)
{
  if (checkCollision(a) == false)
    return;
  //std::cout <<"collision with " << typeid(a).name() <<std::endl;

  if(typeid(a) == typeid(NPC))
  {
    // adjust position?
  }
  else if(typeid(a) == typeid(Weapon))
  {
    // take damage
  }
  else if(typeid(a) == typeid(Projectile))
  {
    // take damage
  }
  else if(typeid(a) == typeid(Collidable))
  {
    // stop movement?

  }

}

/*
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
*/


/*
void Hero::Throw()
{
  ThrowNPC();
  ThrowWeapon();
}

void Hero::Pickup(std::vector< std::shared_ptr<NPC> >& npc_vec,
                 std::vector< std::shared_ptr<Weapon> >& weap_vec)
{
  PickupNPC(npc_vec);
  PickupWeapon(weap_vec);
}

void Hero::Drop()
{
  DropNPC();
  DropWeapon();
}
*/

//-----------------------------
// Private Member Functions
// ----------------------------

/*
void Hero::AttackNPC( Attack atk, double modifier, double rng, std::vector< std::shared_ptr<NPC> >& npc_vec)
{

  // Test Collision of animated weapon hitbox instead of hero hitbox? -> NOT IMPLEMENTED YET
  if (grabbed_npc == nullptr)
  {

    // Play Attack Animation
    switch(atk.getType())
    {
      case Attack::Push :
        setCurrentAnimation(punchAnimation);
        break;

      case Attack::Kick :
        setCurrentAnimation(kickAnimation);
        break;

      case Attack::Smash :
        setCurrentAnimation(punchAnimation);
        break;

    }


    // Test Collision
    for(std::vector< std::shared_ptr<NPC> >::iterator it = npc_vec.begin(); it != npc_vec.end(); ++it)
    {
      if((*it)->getCurrentAnimation() == &(*it)->attackedAnimation)
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
          (*it)->setCurrentAnimation((*it)->attackedAnimation);
          switch ( atk.getType() )
          {
            case Attack::Push :
              std::cout << "NPC pushed" << std::endl;
              (*it)->AddDirection(getOrientation().getType(), modifier * strength * 20 * (1/(*it)->getWeight()), 10);
              break;

            case Attack::Kick :
              std::cout << "NPC kicked" << std::endl;
              (*it)->AddDirection(getOrientation().getType(), 2 * modifier * strength * 20 * (1/(*it)->getWeight()), 10);
              break;

            case Attack::Smash :
              std::cout << "NPC smashed" << std::endl;
              (*it)->AddDirection(getOrientation().getType(), 3 * modifier * strength * 20 * (1/(*it)->getWeight()), 10);
              break;

          }
        }
      }
    }
  }
}
*/

void Hero::Pickup(std::vector<std::shared_ptr<AnimatedEntity>>& vec_ptr_a)
{

  for(auto it = vec_ptr_a.begin(); it != vec_ptr_a.end(); ++it)
  {
    if(typeid(**it) == typeid(NPC) && checkCollision(**it) == true)
    {
      Drop();
      grabbed_npc = std::dynamic_pointer_cast<NPC>(*it);
    }

    if(typeid(**it) == typeid(Weapon) && checkCollision(**it) == true)
    {
      Drop();
      weapon = std::dynamic_pointer_cast<Weapon>(*it);
      weapon->animatedSprite.hitbox.setScale(1, weapon->getRange());
      weapon->animatedSprite.hitbox.setRotation(this->getOrientation().getRotation());
    }
  }
}

void Hero::Drop()
{
  if(grabbed_npc != nullptr)
    grabbed_npc = nullptr;
  else if(weapon != nullptr)
  {
    weapon->animatedSprite.hitbox.setScale(1,1);
    weapon = nullptr;
  }
}

void Hero::Throw()
{
  double throw_speed = 20;
  double throw_distance = 500;

  if(grabbed_npc != nullptr)
  {
    grabbed_npc->AddDirection(getOrientation().getType(), throw_distance, throw_speed);
    //set status to thrown
    grabbed_npc = nullptr;
  }

  if(weapon != nullptr)
  {
    weapon->animatedSprite.hitbox.setScale(1,1);
    weapon->AddDirection(getOrientation().getType(), throw_distance, throw_speed);
    weapon = nullptr;
  }
}



/*
void Hero::PickupWeapon(std::vector< std::shared_ptr<Weapon> >& weap_vec)
{
  if (grabbed_npc == nullptr)
  {
    setCurrentAnimation(grabAnimation);
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
    weapon->AddDirection(getOrientation().getType(), throw_distance, throw_speed);
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

    setCurrentAnimation(grabAnimation);

    for(std::vector< std::shared_ptr<NPC> >::iterator it = npc_vec.begin(); it != npc_vec.end(); ++it)
    {
      if(Collision::BoundingBoxTest( (*it)->animatedSprite.hitbox, this->animatedSprite.hitbox) )
      {
          std::cout << "NPC grabbed" << std::endl;
          grabbed_npc = *it;
          grabbed_npc->setCurrentAnimation(grabbed_npc->grabbedAnimation);
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
    grabbed_npc->setCurrentAnimation(grabbed_npc->defaultAnimation);
    grabbed_npc = nullptr;
  }
}

void Hero::ThrowNPC()
{
  if (grabbed_npc != nullptr)
  {
    grabbed_npc->setCurrentAnimation(grabbed_npc->thrownAnimation);
    double throw_speed = 20;
    double throw_distance = 100 * ( strength/grabbed_npc->getWeight() );
    grabbed_npc->AddDirection(getOrientation().getType(), throw_distance, throw_speed);
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
*/

Weapon Hero::getWeapon()
{
  if (weapon == nullptr)
    return *default_weapon;
  else
    return *weapon;
}
