
#include "hero.h"
#include "npc.h"
#include "weapon.h"


Hero::Hero(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data)
  : AnimatedEntity(AnimatedEntity::HeroType),
    type(t),
    animations(animations),
    data(data),
    idleAnimation(animations.get(data.HeroTable[t].idleAnimationID)),
    moveAnimation(animations.get(data.HeroTable[t].moveAnimationID)),
    dieAnimation(animations.get(data.HeroTable[t].dieAnimationID)),
    deadAnimation(animations.get(data.HeroTable[t].deadAnimationID)),
    attackedAnimation(animations.get(data.HeroTable[t].attackedAnimationID)),
    grabAnimation(animations.get(data.HeroTable[t].grabAnimationID)),
    punchAnimation(animations.get(data.HeroTable[t].punchAnimationID)),
    grabbed_npc(nullptr),
    weapon(nullptr),
    default_weapon(new Weapon(Weapon::Hands, animations, data, 50, 50))
{
  setHitPoints(data.HeroTable[t].hitpoints);
  setSpeed(data.HeroTable[t].speed);
  setPower(data.HeroTable[t].power);

  position.x = 50;
  position.y = 50;

  animatedSprite.setPosition(position.x,position.y);
  animatedSprite.setOrigin(data.HeroTable[t].origin.x,data.HeroTable[type].origin.y);

  setHitbox(*animations.get(Animations::Hitbox).getSpriteSheet(),
          data.HeroTable[t].hitboxDimensions.x,
          data.HeroTable[t].hitboxDimensions.y);

  animatedSprite.setAnimation(moveAnimation); // needs to be initialized
  animatedSprite.setLooped(false);
  animatedSprite.setColor(data.HeroTable[type].color);

  double scale_factor = 0.10;
  animatedSprite.setScale(scale_factor,scale_factor);

  setStatus(AnimatedEntity::Idle);
  playAnimation();

}

void Hero::collideWithEntity(const AnimatedEntity& a, sf::Time dt)
{
  if (checkCollision(a) == false)
    return;

  switch(a.getParentType())
  {
    case AnimatedEntity::HeroType :
      break;

    case AnimatedEntity::NPCType :
      break;

    case AnimatedEntity::WeaponType :
      break;

    case AnimatedEntity::ProjectileType :
      break;

    case AnimatedEntity::CollidableType :
      break;

  }
}

void Hero::MoveGrabbedEntities()
{
  if(grabbed_npc != nullptr)
  {
    grabbed_npc->position.x = position.x;
    grabbed_npc->position.y = position.y - 30;
  }

  getWeapon()->position = position;
  getWeapon()->animatedSprite.setRotation(getOrientation().getRotation());
  getWeapon()->hitbox.setRotation(getOrientation().getRotation());
}

void Hero::PrimaryAttack(std::vector<std::shared_ptr<AnimatedEntity>>& entities)
{
  if(!getWeapon()->primaryAttack->canAttack())
    return;

  getWeapon()->setStatus(AnimatedEntity::AttackingPrimary);
  getWeapon()->playAnimation();
  pAttack(*getWeapon()->primaryAttack, entities);
}

void Hero::SecondaryAttack(std::vector<std::shared_ptr<AnimatedEntity>>& entities)
{
  if(!getWeapon()->secondaryAttack->canAttack())
    return;

  getWeapon()->setStatus(AnimatedEntity::AttackingSecondary);
  getWeapon()->playAnimation();
  pAttack(*getWeapon()->secondaryAttack, entities);

}

void Hero::pAttack(Attack& attack, std::vector<std::shared_ptr<AnimatedEntity>>& entities)
{

  switch(attack.getType())
  {
    case Attack::Standard :
      getWeapon()->hitbox.setScale(1, getWeapon()->getRange());
      getWeapon()->hitbox.setRotation(this->getOrientation().getRotation());
      break;

    case Attack::Shoot :
      auto p1 = std::make_shared<Projectile>( getWeapon()->ammoType->getType(),
                                              animations,
                                              data,
                                              position.x,
                                              position.y,
                                              getOrientation().getType());
      entities.push_back(p1);

      if(getWeapon()->ammoType->getType() == Projectile::BuckShot)
      {
        // works very well for north and south shots, but does not translate for other directions
          auto p2 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, data, position.x-15, position.y-3, getOrientation().getType());
          auto p3 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, data, position.x-10, position.y+3, getOrientation().getType());
          auto p4 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, data, position.x+15, position.y-3, getOrientation().getType());
          auto p5 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, data, position.x+10, position.y+3, getOrientation().getType());

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
  //setCurrentAnimation(grabAnimation);
  setStatus(AnimatedEntity::Grabbing);
  for(auto it = entities.begin(); it != entities.end(); ++it)
  {
    if(typeid(**it) == typeid(NPC) && checkCollision(**it) == true)
    {
      Drop();
      grabbed_npc = std::dynamic_pointer_cast<NPC>(*it);
      grabbed_npc->setStatus(AnimatedEntity::Grabbed);
      grabbed_npc->playAnimation();
      //grabbed_npc->setCurrentAnimation(grabbed_npc->grabbedAnimation);
    }
    else if(typeid(**it) == typeid(Weapon) && checkCollision(**it) == true)
    {
      Drop();
      weapon = std::dynamic_pointer_cast<Weapon>(*it);
      getWeapon()->hitbox.setScale(1, getWeapon()->getRange());
      getWeapon()->hitbox.setRotation(this->getOrientation().getRotation());
      //weapon->hitbox.setOrigin(weapon->animatedSprite.getLocalBounds().width/2, weapon->animatedSprite.getLocalBounds().height);
    }
  }
}

void Hero::Drop()
{
  if(grabbed_npc != nullptr)
    grabbed_npc = nullptr;
  else if(weapon != nullptr)
  {
    weapon->hitbox.setScale(1,1);
    //weapon->hitbox.setOrigin(weapon->animatedSprite.getLocalBounds().width/2, weapon->animatedSprite.getLocalBounds().height/2);
    weapon = nullptr;
  }
}

void Hero::Throw()
{
  double throw_speed = 20;
  double throw_distance = 500;

  if(grabbed_npc != nullptr)
  {
    //grabbed_npc->setCurrentAnimation(grabbed_npc->thrownAnimation);
    grabbed_npc->AddDirection(getOrientation().getType(), throw_distance, throw_speed);
    grabbed_npc->setStatus(AnimatedEntity::Thrown);
    grabbed_npc->playAnimation();
    grabbed_npc = nullptr;
  }

  if(weapon != nullptr)
  {
    weapon->hitbox.setScale(1,1);
    //weapon->hitbox.setOrigin(weapon->animatedSprite.getLocalBounds().width/2, weapon->animatedSprite.getLocalBounds().height/2);
    weapon->AddDirection(getOrientation().getType(), throw_distance, throw_speed);
    weapon->setStatus(AnimatedEntity::Thrown);
    weapon->playAnimation();
    weapon = nullptr;
  }
}

std::shared_ptr<Weapon> Hero::getWeapon()
{
  if(weapon == nullptr)
    return default_weapon;
  else
    return weapon;
}

void Hero::restoreDefaultState()
{
    //setCurrentAnimation(moveAnimation); //delete this line
    getWeapon()->hitbox.setScale(1, 1);
    //setStatus(AnimatedEntity::Moving);
}

void Hero::playAnimation()
{
  switch(getStatus())
  {
    case AnimatedEntity::Idle :
      animatedSprite.pause(); // or animatedSprite.stop() to revert back to first frame
      break;

    case AnimatedEntity::Moving :
      animatedSprite.play(moveAnimation);
      break;

    default :
      animatedSprite.pause();
      break;
  }
}
