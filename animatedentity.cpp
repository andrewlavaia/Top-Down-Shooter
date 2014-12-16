
#include "animatedentity.h"


AnimatedEntity::AnimatedEntity()
  : currentAnimation(nullptr),
    directions_it(directions.begin()),
    distance_travelled(0)

{
    directions.clear();
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
  this->animatedSprite.move( distance.x * interpolation, distance.y * interpolation );
  this->animatedSprite.hitbox.setPosition(this->animatedSprite.getPosition().x, this->animatedSprite.getPosition().y);
}

void AnimatedEntity::Move(Orientation::Type orientation_type, double distance, double speed)
{
  directions_it = directions.insert(directions_it,
                                    Direction(orientation_type,distance,speed,false));
  distance_travelled = 0;
}

void AnimatedEntity::MoveOppo(double d)
{
  Move(getOrientation().getOppo(), d, directions_it->getSpeed());
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
}

bool AnimatedEntity::checkAgroDistance(const AnimatedEntity& entity)
{
  double dist_x = position.x - entity.position.x;
  double dist_y = position.y - entity.position.y;
  double margin = 200;
  double nmargin = margin * -1;

  if( (dist_x < margin && dist_x > nmargin) && (dist_y < margin && dist_y > nmargin) )
    return true;
  else
    return false;
}

