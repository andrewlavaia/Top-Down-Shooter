
#include "hero.h"
#include <iostream>

Hero::Hero(const ResourceHolder<Animation, Animations::ID>& animations)
  : animations(animations),
    grabbed_npc(nullptr),
    weapon(nullptr),
    default_weapon(new Weapon(Weapon::Hands, 50, 50, animations))
{
  position.x = 50;
  position.y = 50;

  setSpeed(10);

  // set up AnimatedSprite
  animatedSprite.setOrigin(29,22);
  animatedSprite.setPosition(position.x,position.y);

  // set hitbox for collision testing
  animatedSprite.setHitbox(20,20);
  //animatedSprite.hitbox.setPosition(position.x,position.y);

  // set Animations
  moveAnimation = std::make_shared<Animation>(animations.get(Animations::Hero_Run));
  grabAnimation = std::make_shared<Animation>(animations.get(Animations::Hero_Grab));
  punchAnimation = std::make_shared<Animation>(animations.get(Animations::Hero_Punch));
  kickAnimation = std::make_shared<Animation>(animations.get(Animations::Hero_Kick));

  double scale_factor = 0.10;
  animatedSprite.setScale(scale_factor,scale_factor);

  setCurrentAnimation(moveAnimation);
  animatedSprite.setLooped(false);
  animatedSprite.play(*getCurrentAnimation());

}

void Hero::collideWithEntity(const AnimatedEntity& a, sf::Time dt)
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

void Hero::MoveGrabbedEntities()
{
  if(grabbed_npc != nullptr)
  {
    grabbed_npc->position.x = position.x;
    grabbed_npc->position.y = position.y - 30;
    // set currentAnimation to "grabbed"
  }

  getWeapon()->position = position;
  getWeapon()->animatedSprite.hitbox.setRotation(getOrientation().getRotation());
}

void Hero::PrimaryAttack(std::vector<std::shared_ptr<AnimatedEntity>>& entities)
{
  if(!getWeapon()->primaryAttack->canAttack())
    return;

  setCurrentAnimation(getWeapon()->primaryAttackAnimation);
  pAttack(*getWeapon()->primaryAttack, entities);
}

void Hero::SecondaryAttack(std::vector<std::shared_ptr<AnimatedEntity>>& entities)
{
  if(!getWeapon()->secondaryAttack->canAttack())
    return;

  setCurrentAnimation(getWeapon()->secondaryAttackAnimation);
  pAttack(*getWeapon()->secondaryAttack, entities);
}

void Hero::pAttack(Attack& attack, std::vector<std::shared_ptr<AnimatedEntity>>& entities)
{

  switch(attack.getType())
  {
    case Attack::Standard :
      getWeapon()->animatedSprite.hitbox.setScale(1, getWeapon()->getRange());
      getWeapon()->animatedSprite.hitbox.setRotation(this->getOrientation().getRotation());
      getWeapon()->setStatus(AnimatedEntity::Attacking);
      break;

    case Attack::Shoot :
      auto p1 = std::make_shared<Projectile>( getWeapon()->ammoType->getType(),
                                              animations,
                                              position.x,
                                              position.y,
                                              getOrientation().getType());
      entities.push_back(p1);

      if(getWeapon()->ammoType->getType() == Projectile::BuckShot)
      {
        // works very well for north and south shots, but does not translate for other directions
          auto p2 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, position.x-15, position.y-3, getOrientation().getType());
          auto p3 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, position.x-10, position.y+3, getOrientation().getType());
          auto p4 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, position.x+15, position.y-3, getOrientation().getType());
          auto p5 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, position.x+10, position.y+3, getOrientation().getType());

          entities.push_back(p2);
          entities.push_back(p3);
          entities.push_back(p4);
          entities.push_back(p5);
      }
      break;
  }

  attack.resetCooldown();

}

void Hero::Pickup(std::vector<std::shared_ptr<AnimatedEntity>>& entities)
{
  setCurrentAnimation(grabAnimation);
  for(auto it = entities.begin(); it != entities.end(); ++it)
  {
    if(typeid(**it) == typeid(NPC) && checkCollision(**it) == true)
    {
      Drop();
      grabbed_npc = std::dynamic_pointer_cast<NPC>(*it);
      grabbed_npc->setCurrentAnimation(grabbed_npc->grabbedAnimation);
    }

    if(typeid(**it) == typeid(Weapon) && checkCollision(**it) == true)
    {
      Drop();
      weapon = std::dynamic_pointer_cast<Weapon>(*it);
      weapon->animatedSprite.hitbox.setOrigin(weapon->animatedSprite.getLocalBounds().width/2,
                                              weapon->animatedSprite.getLocalBounds().height);
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
    weapon->animatedSprite.hitbox.setOrigin(weapon->animatedSprite.getLocalBounds().width/2,
                                            weapon->animatedSprite.getLocalBounds().height/2);
    weapon = nullptr;
  }
}

void Hero::Throw()
{
  double throw_speed = 20;
  double throw_distance = 500;

  if(grabbed_npc != nullptr)
  {
    grabbed_npc->setCurrentAnimation(grabbed_npc->thrownAnimation);
    grabbed_npc->AddDirection(getOrientation().getType(), throw_distance, throw_speed);
    grabbed_npc->setStatus(AnimatedEntity::Thrown);
    grabbed_npc = nullptr;
  }

  if(weapon != nullptr)
  {
    weapon->animatedSprite.hitbox.setScale(1,1);
    weapon->animatedSprite.hitbox.setOrigin(weapon->animatedSprite.getLocalBounds().width/2,
                                            weapon->animatedSprite.getLocalBounds().height/2);
    weapon->AddDirection(getOrientation().getType(), throw_distance, throw_speed);
    weapon = nullptr;
  }
}

std::shared_ptr<Weapon> Hero::getWeapon()
{
  if (weapon == nullptr)
    return default_weapon;
  else
    return weapon;
}

void Hero::restoreDefaultState()
{
    setCurrentAnimation(moveAnimation);
    getWeapon()->animatedSprite.hitbox.setScale(1, 1);
    setStatus(AnimatedEntity::Idle);
}

