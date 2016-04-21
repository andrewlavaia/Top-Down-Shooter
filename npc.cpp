
#include "npc.h"
#include "level.h"
#include "datatables.h"

NPC::NPC(Type t, const ResourceHolder<Animation, Animations::ID>& animations,
         const DataTable& data, double x, double y, std::shared_ptr<Weapon> weap)
  : AnimatedEntity(AnimatedEntity::NPCType),
    type(t),
    temprament(NPC::Aggressive),
    weapon( weap ),
    default_weapon( new Weapon(Weapon::Hands, animations, data, x, y) ),
    idleAnimation(animations.get(data.NPCTable[t].idleAnimationID)),
    moveAnimation(animations.get(data.NPCTable[t].moveAnimationID)),
    dieAnimation(animations.get(data.NPCTable[t].dieAnimationID)),
    deadAnimation(animations.get(data.NPCTable[t].deadAnimationID)),
    attackedAnimation(animations.get(data.NPCTable[t].attackedAnimationID)),
    grabbedAnimation(animations.get(data.NPCTable[t].grabbedAnimationID)),
    thrownAnimation(animations.get(data.NPCTable[t].thrownAnimationID))
{
  setHitPoints(data.NPCTable[t].hitpoints);
  setMaxHitPoints(data.NPCTable[t].hitpoints);
  setSpeed(data.NPCTable[t].speed);
  setPower(data.NPCTable[t].power);

  position.x = x;
  position.y = y;
  animatedSprite.setPosition(position.x, position.y);

  setHitbox(*animations.get(Animations::Hitbox).getSpriteSheet(),
          data.NPCTable[t].hitboxDimensions.x,
          data.NPCTable[t].hitboxDimensions.y);

  setStatus(AnimatedEntity::Moving);
  animatedSprite.play(moveAnimation);
  animatedSprite.setLooped(false);
  animatedSprite.setFrameTime(sf::seconds(0.10));
  animatedSprite.setColor(data.NPCTable[t].color);

  setScaleFactor( data.NPCTable[t].scaleFactor );
  animatedSprite.setScale( getScaleFactor(), getScaleFactor() );
  minimap_color = sf::Color::Red;

  // set AI
  switch(type)
  {
    case NPC::McGinger :
      AddDirection(Orientation::S, 100, getSpeed(), false);
      //AddDirection(Orientation::NW, 100, getSpeed(), true);
      //AddDirection(Orientation::NE, 50, getSpeed(), true);
      //AddDirection(Orientation::SW, 50, getSpeed(), true);

      break;

    case NPC::BigRick :
      AddDirection(Orientation::S,  100, getSpeed(), true);
      AddDirection(Orientation::E,  100, getSpeed(), true);
      AddDirection(Orientation::NW, 100, getSpeed(), true);
      //AddDirection(Orientation::SW, 50, getSpeed(), true);
      break;

    case NPC::Sheep :
      temprament = NPC::Passive;
      AddDirection(Orientation::S,  100, getSpeed(), true);
      AddDirection(Orientation::E,  100, getSpeed(), true);
      AddDirection(Orientation::N,  100, getSpeed(), true);
      AddDirection(Orientation::W,  100, getSpeed(), true);
      minimap_color = sf::Color::Green;
      break;

    default :
      // do nothing
      break;
  }

}

void NPC::Move()
{
  AnimatedEntity::Move();

  if( getWeapon()->getType() != Weapon::Hands )
  {
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
}

void NPC::ifDead()
{
  AnimatedEntity::ifDead();
  if( getStatus() == AnimatedEntity::Dead )
    dropWeapon();
}

void NPC::pAttack(Attack& attack, Level& level)
{

  switch(attack.getType())
  {
    case Attack::Standard :
      getWeapon()->hitbox.setScale( getWeapon()->getScaleFactor(), getWeapon()->getRange() );
      break;

    case Attack::Shoot :
      auto p1 = std::make_shared<Projectile>(getWeapon()->ammoType->getType(), level.animations, level.data, *getWeapon(), position.x, position.y, getWeapon()->animatedSprite.getRotation());
      level.entities.push_back(p1);
      //CreateProjectile(getWeapon()->ammoType->getType(), getWeapon()->position.x, getWeapon()->position.y, getOrientation().getType() );
      break;
  }

  attack.resetCooldown();

}

void NPC::engageHero(const AnimatedEntity& hero, Level& level)
{
    if( getTemprament() == NPC::Aggressive
        && checkDistance( 200, hero )
        && (  getStatus() == AnimatedEntity::Moving
           || getStatus() == AnimatedEntity::Idle )
        && isCollisionOK()
        && !Collision::BoundingBoxTest( hitbox, hero.hitbox )
      )
    {
      setStatus( AnimatedEntity::Moving );
      AddDirection( getRelativeOrientation( hero ).getType(), 0.01, getSpeed() );
      getWeapon()->animatedSprite.setRotation( getRelativeOrientation(hero).getRotation() );

      if( getWeapon()->primaryAttack->canAttack() )
      {
        pAttack(*getWeapon()->primaryAttack, level);
      }

    }
}

std::shared_ptr<Weapon> NPC::getWeapon() const
{
  if( weapon == nullptr )
    return default_weapon;
  else
    return weapon;
}

void NPC::dropWeapon()
{
  weapon = nullptr;
}

void NPC::collideWithEntity(const AnimatedEntity& a, sf::Time dt)
{
  if( !checkCollision( a ) )
    return;

  switch( a.getParentType() )
  {
    case AnimatedEntity::HeroType :
      AddDirection( getRelativeOrientation( a ).getOppo(), 0.01, getSpeed(), false );
      setStatus( AnimatedEntity::Attacked );
      playAnimation();
      break;

    case AnimatedEntity::NPCType :
      AddDirection( getRelativeOrientation( a ).getOppo(), .01, getSpeed(), false );
      setStatus( AnimatedEntity::Attacked );
      playAnimation();
      break;

    case AnimatedEntity::WeaponType :
      if( a.getStatus() != AnimatedEntity::Idle ) // weapons on ground should not hurt
      {
        AddDirectionOppo( 10 );
        setStatus( AnimatedEntity::Attacked );
        playAnimation();

        TakeDamage( a.getPower() ); // should be last function call as it determines death
      }
      break;

    case AnimatedEntity::ProjectileType :
      // first check to see if the projectiles came from the weapon that the NPC is holding
      if( &(*getWeapon()) != &(dynamic_cast<const Projectile&>(a).getOriginatingWeapon()) )
      {
        if( getStatus() != AnimatedEntity::Die ) // special exception so that repeated projectile collisions don't interupt Die animation
        {
          AddDirection( a.getOrientation().getType(), 10, 5, false );
          setStatus( AnimatedEntity::Attacked );
          playAnimation();
        }
        TakeDamage( a.getPower() ); // should be last function call as it determines death
      }
      break;

    case AnimatedEntity::CollidableType :
      // necessary to cast because AnimatedEntity cannot otherwise determine its sub-type
      const Collidable& b = dynamic_cast<const Collidable&>(a);
      switch( b.getType() )
      {
        case Collidable::Exit :
          setStatus( AnimatedEntity::Exited );
          playAnimation();
          std::cout<<"Exit reached."<<std::endl;
          break;

        case Collidable::Boundary :
          AddDirectionOppo( 20 );
          //setOrientation( getOrientation().getOppo() );
          //setStatus( AnimatedEntity::Moving );
          //MoveOneUnit( getOrientation().getOppo(), getSpeed() );
          break;

        case Collidable::SheepPen :
          if( getStatus() != AnimatedEntity::Captured )
          {
            clearDirections();
            setStatus( AnimatedEntity::Captured );
            AddDirection( Orientation::N, 10, getSpeed()/2, true );
            AddDirection( Orientation::E, 10, getSpeed()/2, true );
            AddDirection( Orientation::S, 10, getSpeed()/2, true );
            AddDirection( Orientation::W, 10, getSpeed()/2, true );
            AddDirection( getOrientation().getType(), 15, getSpeed(), false ); // moves last direction added gets looked at first
          }

          //std::cout<<"NPC captured in pen."<<std::endl;
          break;

        default :
          break;
      }
      break;
  }
}

void NPC::playAnimation()
{
  switch( getStatus() )
  {
    case AnimatedEntity::Idle :
      animatedSprite.play( idleAnimation ); // or animatedSprite.stop() to revert back to first frame
      break;

    case AnimatedEntity::Moving :
      animatedSprite.play( moveAnimation );
      break;

    case AnimatedEntity::Attacked :
      animatedSprite.play( attackedAnimation );
      break;

    case AnimatedEntity::Grabbed :
      animatedSprite.play( grabbedAnimation );
      break;

    case AnimatedEntity::Thrown :
      animatedSprite.play( thrownAnimation );
      break;

    case AnimatedEntity::Die :
      animatedSprite.play( dieAnimation );
      break;

    case AnimatedEntity::Dead :
      animatedSprite.play( deadAnimation );
      animatedSprite.setLooped( true );
      break;

    case AnimatedEntity::Captured :
      animatedSprite.play( moveAnimation );
      break;

    default :
      animatedSprite.pause();
      break;
  }
}
