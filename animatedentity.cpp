
#include "animatedentity.h"


AnimatedEntity::AnimatedEntity(ParentType pType)
  : parentType(pType),
    hitpoints(10.0),
    speed(1.0),
    power(1.0),
    status(AnimatedEntity::Idle),
    distance_travelled(0)
{
  directions.clear();
  directions_it = directions.begin();
  animatedSprite.setLooped(false);
  setOrientation(Orientation::S);
}

void AnimatedEntity::MoveAnimatedSprite(double interpolation)
{
  animatedSprite.setOrigin(animatedSprite.getLocalBounds().width/2, animatedSprite.getLocalBounds().height/2);
  sf::Vector2f distance = position - animatedSprite.getPosition();
  animatedSprite.move(distance.x * interpolation, distance.y * interpolation);
  hitbox.setPosition(animatedSprite.getPosition().x, animatedSprite.getPosition().y);
}

void AnimatedEntity::AddDirection(Orientation::Type orientation_type, double distance, double speed, bool rpt)
{
  directions_it = directions.insert(directions_it,
                                     Direction(orientation_type,distance,speed,rpt));
  distance_travelled = 0;
}

void AnimatedEntity::AddDirectionOppo(double d)
{
  AddDirection(getOrientation().getOppo(), d, directions_it->getSpeed());
}

void AnimatedEntity::Move()
{
  //random number generator : rand()%(max-min+1) + min
  //std::cout<<obj.position.x << std::endl;
  if(directions.empty())
  {
      if( !isDead() )
      {
        setStatus( AnimatedEntity::Idle );
        playAnimation();
      }
      return;
  }

  // Check if object has travelled further than distance set in current Direction object
  if(distance_travelled > directions_it->getDistance())
  {
    // If distance exceeded, reset distance counter and have iterator point to next Direction object
    distance_travelled = 0;
    setStatus(AnimatedEntity::Moving); // since next direction object exists, the object must be moving
    playAnimation();

    if(directions_it->isRepeat())
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

  MoveOneUnit(directions_it->getType(), directions_it->getSpeed());

  // update distance travelled
  if ( directions_it->getType() == Orientation::NW ||
       directions_it->getType() == Orientation::NE ||
       directions_it->getType() == Orientation::SW ||
       directions_it->getType() == Orientation::SE)
  {
    // use pythagorean's theorem to calculate distance when heading NE, NW, SE, or SW
    double hypotenuse = sqrt(directions_it->getSpeed() * directions_it->getSpeed() + directions_it->getSpeed() * directions_it->getSpeed());
    distance_travelled += hypotenuse;
  }
  else
  {
    distance_travelled += directions_it->getSpeed();
  }

}


void AnimatedEntity::MoveOneUnit(Orientation::Type o, double spd, bool rotation)
{
  playAnimation();
  setOrientation(o);

  // Rotate Weapons and Projectiles to align with orientation
  if(rotation)
  {
    if( getParentType() == AnimatedEntity::WeaponType
       || getParentType() == AnimatedEntity::ProjectileType )
    {
      animatedSprite.setRotation(getOrientation().getRotation());
    }

  }

  // use pythagorean's theorem to calculate distance when heading NE, NW, SE, or SW
  double hypotenuse = sqrt((spd * spd) + (spd * spd));

  // check orientation and move accordingly
  switch(getOrientation().getType())
  {
    case Orientation::N :
      position.y -= spd;
      break;

    case Orientation::S :
      position.y += spd;
      break;

    case Orientation::E :
      position.x += spd;
      if( getParentType() == AnimatedEntity::HeroType
        || getParentType() == AnimatedEntity::NPCType )
        animatedSprite.setScale(1,1); // restore sprite
      break;

    case Orientation::W :
      position.x -= spd;
      if ( getParentType() == AnimatedEntity::HeroType
         || getParentType() == AnimatedEntity::NPCType )
        animatedSprite.setScale(-1,1); // flip sprite horizontally
      break;

    case Orientation::NW :
      position.x -= hypotenuse/2;
      position.y -= hypotenuse/2;
       if( getParentType() == AnimatedEntity::HeroType
         || getParentType() == AnimatedEntity::NPCType )
        animatedSprite.setScale(-1,1); // flip sprite horizontally
      break;

    case Orientation::NE :
      position.x += hypotenuse/2;
      position.y -= hypotenuse/2;
       if( getParentType() == AnimatedEntity::HeroType
         || getParentType() == AnimatedEntity::NPCType )
        animatedSprite.setScale(1,1); // restore sprite
      break;

    case Orientation::SW :
      position.x -= hypotenuse/2;
      position.y += hypotenuse/2;
      if( getParentType() == AnimatedEntity::HeroType
         || getParentType() == AnimatedEntity::NPCType )
        animatedSprite.setScale(-1,1); // flip sprite horizontally
      break;

    case Orientation::SE :
      position.x += hypotenuse/2;
      position.y += hypotenuse/2;
      if( getParentType() == AnimatedEntity::HeroType
         || getParentType() == AnimatedEntity::NPCType )
        animatedSprite.setScale(1,1); // restore sprite
      break;
  }
}


bool AnimatedEntity::checkCollision(const AnimatedEntity& a) const
{
  if(!isDead() && !a.isDead() && Collision::BoundingBoxTest(hitbox, a.hitbox))
    return true;
  else
    return false;
}

bool AnimatedEntity::isDead() const
{
  if(getStatus() == AnimatedEntity::Dead || getStatus() == AnimatedEntity::Die)
    return true;
  else
    return false;
}

Orientation::Type AnimatedEntity::getRelativeOrientation(const AnimatedEntity& entity) const
{
  double dist_x = position.x - entity.position.x;
  double dist_y = position.y - entity.position.y;
  double margin = 10;
  double nmargin = margin * -1;

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

  if (x_direction == -1 && y_direction == -1)
    return Orientation::NW;
  if (x_direction == -1 && y_direction == 0)
    return Orientation::W;
  if (x_direction == -1 && y_direction == 1)
    return Orientation::SW;
  if (x_direction == 1 && y_direction == -1)
    return Orientation::NE;
  if (x_direction == 1 && y_direction == 0)
    return Orientation::E;
  if (x_direction == 1 && y_direction == 1)
    return Orientation::SE;
  if (x_direction == 0 && y_direction == -1)
    return Orientation::N;
  if (x_direction == 0 && y_direction == 1)
    return Orientation::S;
  if (x_direction == 0 && y_direction == 0) //collision
    return Orientation::S;

    //should not possible to reach here
    return Orientation::S;

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
  if(isDead())
    return;

  directions.clear();
  directions_it = directions.begin();

  setStatus(AnimatedEntity::Die);
  animatedSprite.setLooped(false);
  playAnimation();

}

void AnimatedEntity::TakeDamage(double damage)
{
  hitpoints = hitpoints - damage;
  if(hitpoints <= 0)
    Destroy();
}

void AnimatedEntity::TakeDamageOverTime(double damage, sf::Time dt)
{
  hitpoints = hitpoints - (damage * 10 * dt.asSeconds());
  if(hitpoints <= 0)
    Destroy();
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

