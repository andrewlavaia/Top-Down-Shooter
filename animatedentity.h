
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
    Animation                               defaultAnimation;

    Animation                               CreateAnimation(const sf::Texture& tex, unsigned width, unsigned height, unsigned sprite_count);
    void                                    MoveAnimatedSprite(double interpolation);
    void                                    Move(Orientation::Type orientation_type, double distance, double speed);
    void                                    MoveOppo(double d);

    // getters + setters
    void                                    setOrientation(Orientation::Type t) { orientation.setType(t); }
    Orientation                             getOrientation() {return orientation; }

    Orientation::Type                       getRelativeOrientation(const AnimatedEntity& entity);
    bool                                    checkAgroDistance(const AnimatedEntity& entity);

  private:
    Orientation                             orientation;

};

#endif

