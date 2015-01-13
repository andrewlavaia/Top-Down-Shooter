
#ifndef ANIMATEDENTITY_H
#define ANIMATEDENTITY_H

#include <typeinfo>
#include <SFML/Graphics.hpp>
#include "animatedsprite.h"
#include "animation.h"
#include "direction.h"
#include "texturemanager.h"
#include "collision.h"
#include "orientation.h" // MoveOppo()


class AnimatedEntity
{
  public:

    AnimatedEntity();

    sf::Vector2f                            position;
    AnimatedSprite                          animatedSprite;

    Animation                               defaultAnimation;
    std::vector<Direction>                  directions;
    std::vector<Direction>::iterator        directions_it;

    void                                    MoveAnimatedSprite(double interpolation);
    void                                    AddDirection(Orientation::Type orientation_type, double distance, double speed);
    void                                    AddDirectionOppo(double d);

    void                                    Move();
    bool                                    checkCollision(const AnimatedEntity& a);

    virtual Animation*                      getCurrentAnimation() = 0;
    virtual void                            restoreDefaultAnimation() = 0;
    virtual void                            collideWithEntity(const AnimatedEntity& a) = 0;

    virtual double getSpeed() { return 1; } // needed for NPCs





    void                                    setOrientation(Orientation::Type t) { orientation.setType(t); }
    Orientation                             getOrientation() { return orientation; }

    Orientation::Type                       getRelativeOrientation(const AnimatedEntity& entity);
    bool                                    checkAgroDistance(const AnimatedEntity& entity);

    bool                                    getDestroyFlag() { return destroy_flag; }

  protected:

    double                                  distance_travelled;
    bool                                    destroy_flag;
    Animation                               CreateAnimation(const sf::Texture& tex, unsigned width, unsigned height, unsigned sprite_count);


  private:
    Orientation                             orientation;

    // AI Status (idle, passive, aggressive, defensive)
    // AI status 2 (idle, attacking, walking, running, grabbed,
};

#endif

