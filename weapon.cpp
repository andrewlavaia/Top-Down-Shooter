
#include "weapon.h"
#include "datatables.h"

Weapon::Weapon( Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data, double x, double y )
  : AnimatedEntity( AnimatedEntity::WeaponType ),
    primaryAttack( std::unique_ptr<Attack>( new Attack( data.WeaponTable[t].primaryAttackType, data.WeaponTable[t].primaryAttackSpeed ) ) ),
    secondaryAttack( std::unique_ptr<Attack>( new Attack( data.WeaponTable[t].secondaryAttackType, data.WeaponTable[t].secondaryAttackSpeed ) ) ),
    ammoType( std::unique_ptr<Projectile>( new Projectile( data.WeaponTable[t].ammoType, animations, data, *this ) ) ),
    type( t ),
    range( data.WeaponTable[t].range ),
    ammoCount( data.WeaponTable[t].ammoCount ),
    idleAnimation( animations.get( data.WeaponTable[t].idleAnimationID ) ),
    moveAnimation( animations.get( data.WeaponTable[t].moveAnimationID ) ),
    dieAnimation( animations.get( data.WeaponTable[t].dieAnimationID ) ),
    primaryAttackAnimation( animations.get( data.WeaponTable[t].primaryAttackAnimationID ) ),
    secondaryAttackAnimation( animations.get( data.WeaponTable[t].secondaryAttackAnimationID ) )
{
  setHitPoints( data.WeaponTable[t].hitpoints );
  setMaxHitPoints( data.WeaponTable[t].hitpoints );
  setSpeed( data.WeaponTable[t].speed );
  setPower( data.WeaponTable[t].power );

  position.x = x; //rand()%1024;    //random number generator : rand()%(max-min+1) + min
  position.y = y; //rand()%768;
  animatedSprite.setPosition(position.x, position.y);

  setHitbox( *animations.get(Animations::Hitbox).getSpriteSheet(),
              data.WeaponTable[t].hitboxDimensions.x,
              data.WeaponTable[t].hitboxDimensions.y );

  setStatus( AnimatedEntity::Idle );
  animatedSprite.play( idleAnimation );
  animatedSprite.setLooped( false );
  //animatedSprite.setFrameTime( sf::seconds(0.16) );
  animatedSprite.setColor( data.WeaponTable[t].color );

  setScaleFactor( data.WeaponTable[t].scaleFactor );
  animatedSprite.setScale( getScaleFactor(), getScaleFactor() );

  animatedSprite.setRotation( 90 );
  hitbox.setRotation( 90 );

  minimap_color = sf::Color::Black;

  // if no specific origin dimensions are set, use center of sprite, otherwise use specific dimensions
  if( data.WeaponTable[t].originDimensions.x == 0 && data.WeaponTable[t].originDimensions.y == 0)
  {
    animatedSprite.setOrigin(animatedSprite.getLocalBounds().width/2, animatedSprite.getLocalBounds().height/2);
  }
  else
  {
    animatedSprite.setOrigin(data.WeaponTable[t].originDimensions.x, data.WeaponTable[t].originDimensions.y);
  }
}


void Weapon::collideWithEntity( const AnimatedEntity& a, sf::Time dt )
{
  if( checkCollision( a ) == false )
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

void Weapon::playAnimation()
{
  animatedSprite.setLooped( false );

  switch( getStatus() )
  {
    case AnimatedEntity::Idle :
      animatedSprite.play( idleAnimation );
      break;

    case AnimatedEntity::Moving :
      animatedSprite.play( moveAnimation );
      break;

    case AnimatedEntity::Thrown :
      animatedSprite.play( moveAnimation );
      break;

    case AnimatedEntity::AttackingPrimary :
      animatedSprite.play( primaryAttackAnimation );
      //std::cout << "play animation - " << primaryAttackAnimation.getSize() << std::endl;
      break;

    case AnimatedEntity::AttackingSecondary :
      animatedSprite.play( secondaryAttackAnimation );
      break;

    default :
      animatedSprite.pause();
      break;
  }
}

