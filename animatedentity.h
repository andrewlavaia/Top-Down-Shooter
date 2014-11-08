
#ifndef ANIMATEDENTITY_H
#define ANIMATEDENTITY_H

#include <SFML/Graphics.hpp>
#include "animatedsprite.h"
#include "animation.h"
#include "direction.h"
#include "texturemanager.h"
#include "orientation.h" // MoveOppo()


class AnimatedEntity
{
  public:
                                            AnimatedEntity();

    sf::Vector2f                            position;
    AnimatedSprite                          animatedSprite;
    Animation*                              currentAnimation;
    std::vector<Direction>                  directions;
    std::vector<Direction>::iterator        directions_it;
    double                                  distance_travelled;

    Animation                               CreateAnimation(const sf::Texture& tex, unsigned width, unsigned height, unsigned sprite_count);
    void                                    MoveAnimatedSprite(double interpolation);
    void                                    MoveOppo(double d);

  private:

    //Orientation                             orientation;
    //std::shared_ptr<TextureManager>         texture_ptr;



};

#endif

