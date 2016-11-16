
#include "hero.h"
#include "datatables.h"
#include <cmath> // trig functions sin and cos


Hero::Hero(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data)
  : AnimatedEntity(AnimatedEntity::HeroType),
    type(t),
    animations(animations),
    data(data),
    grabbed_npc(nullptr),
    weapon(nullptr),
    default_weapon(new Weapon(Weapon::Hands, animations, data, 50, 50)),
    idleAnimation(animations.get(data.HeroTable[t].idleAnimationID)),
    moveAnimation(animations.get(data.HeroTable[t].moveAnimationID)),
    dieAnimation(animations.get(data.HeroTable[t].dieAnimationID)),
    deadAnimation(animations.get(data.HeroTable[t].deadAnimationID)),
    attackedAnimation(animations.get(data.HeroTable[t].attackedAnimationID)),
    grabAnimation(animations.get(data.HeroTable[t].grabAnimationID))
{
  setHitPoints(data.HeroTable[t].hitpoints);
  setMaxHitPoints(data.HeroTable[t].hitpoints);
  setSpeed(data.HeroTable[t].speed);
  setPower(data.HeroTable[t].power);

  position.x = 100;
  position.y = 100;
  animatedSprite.setPosition(position.x,position.y);

  setHitbox(*animations.get(Animations::Hitbox).getSpriteSheet(),
          data.HeroTable[t].hitboxDimensions.x,
          data.HeroTable[t].hitboxDimensions.y);

  animatedSprite.setAnimation(idleAnimation); // needs to be initialized
  animatedSprite.setLooped(false);
  animatedSprite.setColor(data.HeroTable[type].color);
  animatedSprite.setFrameTime(sf::seconds(0.10)); // 6 fps is .166667

  setScaleFactor( data.HeroTable[t].scaleFactor );
  animatedSprite.setScale( getScaleFactor(), getScaleFactor() );

  setStatus(AnimatedEntity::Idle);
  playAnimation();

  minimap_color = sf::Color::Blue;

  animatedSprite.setOrigin(animatedSprite.getLocalBounds().width/2, animatedSprite.getLocalBounds().height/2);

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
      if( dynamic_cast<const NPC&>(a).getTemprament() == NPC::Aggressive )
      {
        //TakeDamage( a.getPower() );
      }
      if( &(*grabbed_npc) != &a ) // grabbed npc's should not trigger collisions
        MoveOneUnit( getRelativeOrientation( a ).getOppo(), getSpeed() );
      break;

    case AnimatedEntity::WeaponType :
      break;

    case AnimatedEntity::ProjectileType :
      // first check to see if the projectiles came from the weapon that the NPC is holding
      if( &(*getWeapon()) != &(dynamic_cast<const Projectile&>(a).getOriginatingWeapon()) )
      {
        setStatus( AnimatedEntity::Attacked );
        playAnimation();
        MoveOneUnit( a.getOrientation().getType(), getSpeed() );
        TakeDamage( a.getPower() );
      }
      break;

    case AnimatedEntity::CollidableType :
      // necessary to cast because AnimatedEntity cannot otherwise determine its sub-type
      switch( dynamic_cast<const Collidable&>(a).getType() )
      {
        case Collidable::Exit :
          setStatus( AnimatedEntity::Exited );
          playAnimation();
          std::cout<<"Exit reached."<<std::endl;
          break;

        case Collidable::Boundary :
          setStatus( AnimatedEntity::Impassable ); // how should I use this?
          MoveOneUnit( getOrientation().getOppo(), getSpeed() ); // can't use getRelativeOrientation because that would use the origin of boundary
          MoveOneUnit( getOrientation().getType(), getSpeed() );
          MoveOneUnit( getOrientation().getType(), getSpeed() );
          break;

        default :
          break;
      }
      break;

  }
}

void Hero::MoveGrabbedEntities()
{
  if( grabbed_npc != nullptr )
  {
    grabbed_npc->position.x = position.x;
    grabbed_npc->position.y = position.y - 30;
  }

  const double PI = 3.14159265;
  double r = getWeapon()->animatedSprite.getRotation();
  getWeapon()->position.x = position.x + ( 15 * sin( r * PI/180 ) );
  getWeapon()->position.y = position.y - ( 15 * cos( r * PI/180 ) ) + 10; // minus because cos(180) = -1, and cos(0) = 1,
                                                                          // 10 added back to put weapon closer to hands
  // flip grabbed weapon if it is pointed towards left half of screen
  if( getWeapon()->animatedSprite.getRotation() > 180 )
  {
    getWeapon()->animatedSprite.setScale( -1 * getWeapon()->getScaleFactor(), getWeapon()->getScaleFactor() );
  }
  else
  {
    getWeapon()->animatedSprite.setScale( getWeapon()->getScaleFactor(), getWeapon()->getScaleFactor() );
  }

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
      getWeapon()->hitbox.setScale( getWeapon()->getScaleFactor(), getWeapon()->getRange() );
      break;

    case Attack::Shoot :
      if(getWeapon()->getAmmo() > 0 )
      {
          // Should this be optimized? 5 projectiles constructed every shot. 4 are then immediately destructed if not buckshot.
          auto p1 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, data, *getWeapon(), position.x, position.y, getWeapon()->animatedSprite.getRotation());
          auto p2 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, data, *getWeapon(), position.x, position.y, getWeapon()->animatedSprite.getRotation()-5);
          auto p3 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, data, *getWeapon(), position.x, position.y, getWeapon()->animatedSprite.getRotation()-3);
          auto p4 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, data, *getWeapon(), position.x, position.y, getWeapon()->animatedSprite.getRotation()+3);
          auto p5 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), animations, data, *getWeapon(), position.x, position.y, getWeapon()->animatedSprite.getRotation()+5);

        switch( getWeapon()->ammoType->getType() )
        {
          case Projectile::BuckShot :
            entities.push_back(p1);
            entities.push_back(p2);
            entities.push_back(p3);
            entities.push_back(p4);
            entities.push_back(p5);
            break;

          default:
            entities.push_back(p1);
            break;
        }
        getWeapon()->reduceAmmo();
      } // end if(ammoCount > 0 )
      break;

    case Attack::Thrust :


      break;
  }

  attack.resetCooldown();

}

void Hero::Pickup( std::vector<std::shared_ptr<AnimatedEntity>>& entities )
{
  setStatus( AnimatedEntity::Grabbing );
  for( auto it = entities.begin(); it != entities.end(); ++it )
  {
    if( typeid( **it ) == typeid( NPC ) && checkCollision( **it ) == true )
    {
      Drop();
      grabbed_npc = std::dynamic_pointer_cast<NPC>( *it );
      grabbed_npc->setStatus( AnimatedEntity::Grabbed );
      grabbed_npc->playAnimation();
    }
    else if( typeid( **it ) == typeid( Weapon ) && checkCollision( **it ) == true )
    {
      Drop();
      weapon = std::dynamic_pointer_cast<Weapon>(*it);
      getWeapon()->hitbox.setScale( getWeapon()->getScaleFactor(), getWeapon()->getRange() );
    }
  }
}

void Hero::Drop()
{
  if( grabbed_npc != nullptr )
  {
    grabbed_npc = nullptr;
  }
  else if( weapon != nullptr )
  {
    weapon->hitbox.setScale( getWeapon()->getScaleFactor(), getWeapon()->getScaleFactor() );
    weapon = nullptr;
  }
}

void Hero::Throw()
{
  double throw_speed = 20;
  double throw_distance = 500;

  if( grabbed_npc != nullptr )
  {
    grabbed_npc->AddDirection( getOrientation().getType(), throw_distance, throw_speed );
    grabbed_npc->setOrientation( getOrientation().getType() );
    grabbed_npc->setStatus( AnimatedEntity::Thrown );
    grabbed_npc->playAnimation();
    grabbed_npc = nullptr;
  }

  if( weapon != nullptr )
  {
    weapon->hitbox.setScale( getWeapon()->getScaleFactor(), getWeapon()->getScaleFactor() );
    weapon->AddDirection( getOrientation().getType(), throw_distance, throw_speed );
    weapon->setStatus( AnimatedEntity::Thrown );
    weapon->playAnimation();
    weapon = nullptr;
  }
}

std::shared_ptr<Weapon> Hero::getWeapon()
{
  if( weapon == nullptr )
    return default_weapon;
  else
    return weapon;
}

void Hero::playAnimation()
{
  animatedSprite.setLooped( false );

  switch( getStatus() )
  {
    case AnimatedEntity::Idle :
      animatedSprite.play( idleAnimation ); // or animatedSprite.stop() to revert back to first frame
      animatedSprite.setLooped( true );
      break;

    case AnimatedEntity::Moving :
      animatedSprite.play( moveAnimation );
      break;

    default :
      animatedSprite.pause();
      break;
  }
}
