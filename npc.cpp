
#include "npc.h"
#include "datatables.h"

NPC::NPC(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data, double x, double y)
  : AnimatedEntity(AnimatedEntity::NPCType),
    type(t),
    idleAnimation(animations.get(data.NPCTable[t].idleAnimationID)),
    moveAnimation(animations.get(data.NPCTable[t].moveAnimationID)),
    dieAnimation(animations.get(data.NPCTable[t].dieAnimationID)),
    deadAnimation(animations.get(data.NPCTable[t].deadAnimationID)),
    attackedAnimation(animations.get(data.NPCTable[t].attackedAnimationID)),
    grabbedAnimation(animations.get(data.NPCTable[t].grabbedAnimationID)),
    thrownAnimation(animations.get(data.NPCTable[t].thrownAnimationID))
{
  setHitPoints(data.NPCTable[t].hitpoints);
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

  setScaleFactor(2);
  animatedSprite.setScale( getScaleFactor(), getScaleFactor() );

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

    default :
      // do nothing
      break;
  }

}

void NPC::collideWithEntity(const AnimatedEntity& a, sf::Time dt)
{
  if( !checkCollision( a ) )
    return;

  switch(a.getParentType())
  {
    case AnimatedEntity::HeroType :
      break;

    case AnimatedEntity::NPCType :
      break;

    case AnimatedEntity::WeaponType :
      if( a.getStatus() != AnimatedEntity::Idle ) // weapons on ground should not hurt
      {
        AddDirectionOppo( 10 );
        setStatus( AnimatedEntity::Attacked );
        playAnimation();

        TakeDamage( a.getPower() ); // should be last function call as it determines death
        std::cout<<getHP()<<std::endl;
      }
      break;

    case AnimatedEntity::ProjectileType :
      AddDirection( a.getOrientation().getType(), 10, 5, false );
      setStatus( AnimatedEntity::Attacked );
      playAnimation();

      TakeDamage( a.getPower() ); // should be last function call as it determines death

      std::cout<<getHP()<<std::endl;
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
