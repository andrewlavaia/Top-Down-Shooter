
#include "animatedentity.h"


AnimatedEntity::AnimatedEntity( ParentType pType )
  : parentType( pType ),
    hitpoints( 10.0 ),
    speed( 1.0 ),
    power( 1.0 ),
    status( AnimatedEntity::Idle ),
    distance_travelled( 0 ),
    scaleFactor( 1.0 ),
    collisionOK( true ),
    minimap_color( sf::Color::Transparent )
    //collisionCooldown( sf::Time::Zero )
{
  directions.clear();
  directions_it = directions.begin();
  animatedSprite.setLooped( false );
  setOrientation( Orientation::S );

  healthbar.setPosition( position.x - 5, position.y - 25 );
  healthbar.setSize( sf::Vector2f( 20, 5 ) );
  healthbar.setFillColor( sf::Color::Green );

  healthbar_damage = healthbar;
  healthbar_damage.setFillColor( sf::Color::Red );
}

void AnimatedEntity::MoveAnimatedSprite(double interpolation)
{

  sf::Vector2f distance = position - animatedSprite.getPosition();
  animatedSprite.move(distance.x * interpolation, distance.y * interpolation);
  hitbox.setPosition(animatedSprite.getPosition().x, animatedSprite.getPosition().y);

  healthbar.setPosition( position.x - 5, position.y - 25);
  healthbar_damage.setPosition( position.x - 5, position.y - 25 );
  healthbar.setSize( sf::Vector2f( ( getHP() / getMaxHP() ) * 20, 5 ) );

}

void AnimatedEntity::AddDirection(Orientation::Type orientation_type, double distance, double speed, bool rpt, double degrees)
{
  // override current direction if repeat is off
  if( !directions.empty() && !directions_it->isRepeat() )
  {
    directions_it = directions.erase( directions_it );

    // if last direction reached after incrementing iterator, reset to beginning
    if( directions_it == directions.end() )
    {
      directions_it = directions.begin();
    }
  }

  directions_it = directions.insert( directions_it,
                                     Direction( orientation_type, distance, speed, rpt, degrees ) );
  distance_travelled = 0;

}

void AnimatedEntity::AddDirectionOppo(double d)
{
  AddDirection( getOrientation().getOppo(), d, getSpeed() );
  collisionOK = false;
}

void AnimatedEntity::Move()
{
  // Attacking Weapons need to be excluded from the rest of this code
  if( getStatus() == AnimatedEntity::AttackingPrimary || getStatus() == AnimatedEntity::AttackingSecondary )
  {
    return;
  }

  if( directions.empty() )
  {
    if( !isDead() )
    {
      setStatus( AnimatedEntity::Idle ); //!!! causing issues with animations not playing for weapons
      playAnimation();
    }
    return;
  }

  // Check if object has travelled further than distance set in current Direction object
  if( distance_travelled > directions_it->getDistance() )
  {
    // If distance exceeded, reset distance counter and have iterator point to next Direction object
    distance_travelled = 0;
    if( getStatus() != AnimatedEntity::Captured )
      setStatus( AnimatedEntity::Moving ); // since next direction object exists, the object must be moving
    collisionOK = true;
    playAnimation();

    if( directions_it->isRepeat() )
    {
      directions_it++;
    }
    else
    {
      directions_it = directions.erase(directions_it);
    }

    // if last direction reached after incrementing iterator, reset to beginning
    if(directions_it == directions.end())
    {
      directions_it = directions.begin();
    }
  }

  setOrientation( directions_it->getType() );


  if( parentType == ProjectileType )
  {
    MoveOneUnit( directions_it->getRotation(), directions_it->getSpeed() );
  }
  else
  {
    MoveOneUnit( directions_it->getType(), directions_it->getSpeed() );

     // update distance travelled
    if ( directions_it->getType() == Orientation::NW ||
         directions_it->getType() == Orientation::NE ||
         directions_it->getType() == Orientation::SW ||
         directions_it->getType() == Orientation::SE)
    {
      // use pythagorean's theorem to calculate distance when heading NE, NW, SE, or SW
      double hypotenuse = sqrt( directions_it->getSpeed() * directions_it->getSpeed()
                                + directions_it->getSpeed() * directions_it->getSpeed() );
      distance_travelled += hypotenuse;
    }
    else
    {
      distance_travelled += directions_it->getSpeed();
    }
  }

}

void AnimatedEntity::MoveOneUnit(double rotation, double speed)
{
  playAnimation();

  // Projectiles align with current rotation when fired
  if( getParentType() == AnimatedEntity::ProjectileType )
  {
    animatedSprite.setRotation( rotation );
    setOrientation( rotation );
  }

  int x_remainder; // int because modulus operator does not work on double
  double x;
  double y;

  // calculate horizontal factor
  if( rotation < 90.0 )
  {
    x_remainder = (int)rotation % 91;
    x = x_remainder / 90.0;
  }
  else if(rotation > 270.0 )
  {
    x_remainder = ( (int)rotation - 360 ) % 91;
    x = x_remainder / 90.0;
  }
  else
  {
    x_remainder = ( (int)rotation - 180 ) % 91;
    x = -1 * x_remainder / 90.0;
  }

  // calculate vertical factor
  y = 1 - std::abs( x );
  if( rotation < 90.0 || rotation > 270.0 )
  {
    y = y*-1;
  }

  // calculate total distance using pythagorean's theorem and
  // apply to factors to determine movement
  double hypotenuse;
  double x_movement;
  double y_movement;

  hypotenuse = 1/std::sqrt( ( x * x ) + ( y * y ) );
  x_movement = hypotenuse * x;
  y_movement = hypotenuse * y;

  /*
  std::cout<<x<<", "<<y<<std::endl;
  std::cout<<"hypotenuse: "<<hypotenuse<<std::endl;
  std::cout<<"move coords: "<<x_movement<<", "<<y_movement<<std::endl;
  */

  // Move entity
  position.x += ( speed * x_movement );
  position.y += ( speed * y_movement );

  distance_travelled += hypotenuse;

}

void AnimatedEntity::MoveOneUnit(Orientation::Type o, double spd, bool rotation)
{
  playAnimation();
  setOrientation(o);

  // Rotate Projectiles to align with orientation when fired
  if( getParentType() == AnimatedEntity::ProjectileType )
  {
    animatedSprite.setRotation( getOrientation().getRotation() );
  }

  // use pythagorean's theorem to calculate distance when heading NE, NW, SE, or SW
  double hypotenuse = sqrt((spd * spd) + (spd * spd));

  // check orientation and move accordingly
  switch( o )
  {
    case Orientation::N :
      position.y -= spd;
      break;

    case Orientation::S :
      position.y += spd;
      break;

    case Orientation::E :
      position.x += spd;
      if( ( getParentType() == AnimatedEntity::HeroType || getParentType() == AnimatedEntity::NPCType )
          && getStatus() != AnimatedEntity::Attacked )
      {
        animatedSprite.setScale( getScaleFactor(), getScaleFactor() ); // restore sprite
      }
      break;

    case Orientation::W :
      position.x -= spd;
      if( ( getParentType() == AnimatedEntity::HeroType || getParentType() == AnimatedEntity::NPCType )
          && getStatus() != AnimatedEntity::Attacked )
      {
        animatedSprite.setScale( -1 * getScaleFactor(), getScaleFactor() ); // flip sprite horizontally
      }
      break;

    case Orientation::NW :
      position.x -= hypotenuse/2;
      position.y -= hypotenuse/2;
      if( ( getParentType() == AnimatedEntity::HeroType || getParentType() == AnimatedEntity::NPCType )
          && getStatus() != AnimatedEntity::Attacked )
      {
        animatedSprite.setScale( -1 * getScaleFactor(), getScaleFactor() ); // flip sprite horizontally
      }
      break;

    case Orientation::NE :
      position.x += hypotenuse/2;
      position.y -= hypotenuse/2;
      if( ( getParentType() == AnimatedEntity::HeroType || getParentType() == AnimatedEntity::NPCType )
          && getStatus() != AnimatedEntity::Attacked )
      {
        animatedSprite.setScale( getScaleFactor(), getScaleFactor() ); // restore sprite
      }
      break;

    case Orientation::SW :
      position.x -= hypotenuse/2;
      position.y += hypotenuse/2;
      if( ( getParentType() == AnimatedEntity::HeroType || getParentType() == AnimatedEntity::NPCType )
          && getStatus() != AnimatedEntity::Attacked )
      {
        animatedSprite.setScale( -1 * getScaleFactor(), getScaleFactor() ); // flip sprite horizontally
      }

      break;

    case Orientation::SE :
      position.x += hypotenuse/2;
      position.y += hypotenuse/2;
      if( ( getParentType() == AnimatedEntity::HeroType || getParentType() == AnimatedEntity::NPCType )
          && getStatus() != AnimatedEntity::Attacked )
      {
        animatedSprite.setScale( getScaleFactor(), getScaleFactor() ); // restore sprite
      }

      break;
  }
}

bool AnimatedEntity::checkCollision( const AnimatedEntity& a ) const
{
  if( this != &a && checkDistance(100, a) && isCollisionOK() && a.isCollisionOK() && Collision::BoundingBoxTest( hitbox, a.hitbox ) )
    return true;
  else
    return false;
}

bool AnimatedEntity::isDead() const
{
  if( getStatus() == AnimatedEntity::Dead || getStatus() == AnimatedEntity::Die )
    return true;
  else
    return false;
}

void AnimatedEntity::ifDead()
{
  if( getStatus() == AnimatedEntity::Die && !animatedSprite.isPlaying() ) // if dying with no active die animation, entity should be dead
  {
    setStatus( AnimatedEntity::Dead );
    playAnimation();
    collisionOK = false;
  }
}

Orientation AnimatedEntity::getRelativeOrientation( const AnimatedEntity& entity ) const
{
  Orientation o;

  const double dist_x = position.x - entity.position.x;
  const double dist_y = position.y - entity.position.y;
  const double margin = 10;
  const double nmargin = margin * -1;

  int x_direction = 0;
  int y_direction = 0;

  if(dist_x > margin) // entity is to the left
    x_direction = -1;
  if(dist_x < nmargin) // entity is to the right
    x_direction = 1;
  if(dist_y > margin) // entity is above
    y_direction = -1;
  if(dist_y < nmargin) // entity is below
    y_direction = 1;

  if( x_direction == -1 && y_direction == -1 )
    o.setType( Orientation::NW );
  if( x_direction == -1 && y_direction == 0 )
    o.setType( Orientation::W );
  if( x_direction == -1 && y_direction == 1 )
    o.setType( Orientation::SW );
  if( x_direction == 1 && y_direction == -1 )
    o.setType( Orientation::NE );
  if( x_direction == 1 && y_direction == 0 )
    o.setType( Orientation::E );
  if( x_direction == 1 && y_direction == 1 )
    o.setType( Orientation::SE );
  if( x_direction == 0 && y_direction == -1 )
    o.setType( Orientation::N );
  if( x_direction == 0 && y_direction == 1 )
    o.setType( Orientation::S );
  if( x_direction == 0 && y_direction == 0 ) //collision
    o.setType( Orientation::S );

  return o;

}

bool AnimatedEntity::checkDistance(double distance, const AnimatedEntity& entity) const
{
  double dist_x = position.x - entity.position.x;
  double dist_y = position.y - entity.position.y;
  double ndistance = distance * -1;

  if( (dist_x < distance && dist_x > ndistance) && (dist_y < distance && dist_y > ndistance) )
    return true;
  else
    return false;
}

void AnimatedEntity::Destroy()
{
  if( isDead() ) // is this needed???
    return;

  clearDirections();

  setStatus( AnimatedEntity::Die );
  animatedSprite.setLooped( false );
  playAnimation();

}

void AnimatedEntity::TakeDamage( double damage )
{
  if( getStatus() == AnimatedEntity::Die || getStatus() == AnimatedEntity::Dead )
    return;

  hitpoints = hitpoints - damage;
  if( hitpoints <= 0 )
    Destroy();
}

void AnimatedEntity::TakeDamageOverTime( double damage, sf::Time dt )
{
  if( getStatus() == AnimatedEntity::Die || getStatus() == AnimatedEntity::Dead )
    return;

  hitpoints = hitpoints - ( damage * 10 * dt.asSeconds() );
  if( hitpoints <= 0 )
    Destroy();
}

void AnimatedEntity::clearDirections()
{
  directions.clear();
  directions_it = directions.begin();
}


void AnimatedEntity::setHitbox(const sf::Texture& texture, unsigned width, unsigned height)
{
  // set hitbox for collision testing
  hitbox.setTexture(texture);
  hitbox.setTextureRect(sf::IntRect(0, 0, width, height));
  hitbox.setOrigin(width/2, height/2);
  hitbox.setPosition(animatedSprite.getPosition());

  assert(width <= 2000 && height <= 2000); // maximum texture size, this can be increased by using a larger hitbox image
}

