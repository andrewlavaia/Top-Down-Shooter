
#include "animatedentity.h"


AnimatedEntity::AnimatedEntity()
  : distance_travelled(0),
    destroy_flag(false)
{
    directions.clear();
    directions_it = directions.begin();
    setOrientation(Orientation::S);
}

Animation AnimatedEntity::CreateAnimation(const sf::Texture& tex, unsigned width, unsigned height, unsigned sprite_count)
{
  Animation animation;
  animation.setSpriteSheet(tex);
  for (unsigned i = 0; i < sprite_count; ++i)
  {
    animation.addFrame(sf::IntRect( i * width, 0, width,  height));
  }

  return animation;
}

void AnimatedEntity::MoveAnimatedSprite(double interpolation)
{
  animatedSprite.setOrigin(animatedSprite.getLocalBounds().width/2, animatedSprite.getLocalBounds().height/2);
  sf::Vector2f distance = this->position - this->animatedSprite.getPosition();
  this->animatedSprite.move(distance.x * interpolation, distance.y * interpolation);
  this->animatedSprite.hitbox.setPosition(this->animatedSprite.getPosition().x, this->animatedSprite.getPosition().y);
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
  if(directions.empty() == true) { return; }

  // Check if object has travelled further than distance set in current Direction object
  if(distance_travelled > directions_it->getDistance())
  {
    // If distance exceeded, reset distance counter and have iterator point to next Direction object
    distance_travelled = 0;

    restoreDefaultAnimation(); // should this be here?

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

  // update orientation
  setOrientation(directions_it->getType());

  // use pythagorean's theorem to calculate distance when heading NE, NW, SE, or SW
  double hypotenuse = sqrt(directions_it->getSpeed() * directions_it->getSpeed() + directions_it->getSpeed() * directions_it->getSpeed());

  // check direction and move object accordingly
  switch(directions_it->getType())
  {
    case Orientation::N :
      position.y -= directions_it->getSpeed();
      animatedSprite.setRotation(0);
      break;

    case Orientation::S :
      position.y += directions_it->getSpeed();
      animatedSprite.setRotation(180);
      break;

    case Orientation::E :
      position.x += directions_it->getSpeed();
      animatedSprite.setRotation(90);
      break;

    case Orientation::W :
      position.x -= directions_it->getSpeed();
      animatedSprite.setRotation(270);
      break;

    case Orientation::NW :
      position.x -= hypotenuse/2;
      position.y -= hypotenuse/2;
      animatedSprite.setRotation(315);
      break;

    case Orientation::NE :
      position.x += hypotenuse/2;
      position.y -= hypotenuse/2;
      animatedSprite.setRotation(45);
      break;

    case Orientation::SW :
      position.x -= hypotenuse/2;
      position.y += hypotenuse/2;
      animatedSprite.setRotation(225);
      break;

    case Orientation::SE :
      position.x += hypotenuse/2;
      position.y += hypotenuse/2;
      animatedSprite.setRotation(135);
      break;

  }

  // update distance travelled
  if ( directions_it->getType() == Orientation::NW ||
       directions_it->getType() == Orientation::NE ||
       directions_it->getType() == Orientation::SW ||
       directions_it->getType() == Orientation::SE)
  {
    distance_travelled += hypotenuse;
  }
  else
  {
    distance_travelled += directions_it->getSpeed();
  }

}

bool AnimatedEntity::checkCollision(const AnimatedEntity& a)
{
  if(Collision::BoundingBoxTest(animatedSprite.hitbox, a.animatedSprite.hitbox))
    return true;
  else
    return false;
}

Orientation::Type AnimatedEntity::getRelativeOrientation(const AnimatedEntity& entity)
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

bool AnimatedEntity::checkDistance(double distance, const AnimatedEntity& entity)
{
  double dist_x = position.x - entity.position.x;
  double dist_y = position.y - entity.position.y;
  double ndistance = distance * -1;

  if( (dist_x < distance && dist_x > ndistance) && (dist_y < distance && dist_y > ndistance) )
    return true;
  else
    return false;
}

