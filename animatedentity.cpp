
#include "animatedentity.h"


AnimatedEntity::AnimatedEntity()
  : currentAnimation(nullptr),
    directions_it(directions.begin()),
    distance_travelled(0)

{
    directions.clear();
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

void AnimatedEntity::MoveOppo(double d)
{
  Orientation o;
  o.setType(directions_it->getType());
  directions_it = directions.insert(directions_it + 1,
                                    Direction(o.getOppo(),d,directions_it->getSpeed(),false));
  distance_travelled = 0;
}
