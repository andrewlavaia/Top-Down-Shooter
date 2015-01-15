
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
    virtual ~AnimatedEntity() {}

    sf::Vector2f                            position;
    AnimatedSprite                          animatedSprite;

    Animation                               defaultAnimation;

    void                                    Move();
    void                                    MoveAnimatedSprite(double interpolation);
    void                                    AddDirection(Orientation::Type orientation_type, double distance, double speed, bool rpt = false);
    void                                    AddDirectionOppo(double d);

    virtual Animation*                      getCurrentAnimation() = 0;
    virtual void                            restoreDefaultAnimation() = 0;
    virtual void                            collideWithEntity(const AnimatedEntity& a) = 0;

    virtual double getSpeed() { return 1; } // needed for NPCs

    void                                    setOrientation(Orientation::Type t) { orientation.setType(t); }
    Orientation                             getOrientation() { return orientation; }
    Orientation::Type                       getRelativeOrientation(const AnimatedEntity& entity);

    bool                                    checkCollision(const AnimatedEntity& a);
    bool                                    checkDistance(double distance, const AnimatedEntity& entity);
    bool                                    isDestroyed() { return destroy_flag; }
    bool                                    isNotMoving() { return directions.empty(); }

  protected:
    Animation                               CreateAnimation(const sf::Texture& tex, unsigned width, unsigned height, unsigned sprite_count);
    void                                    Destroy() { destroy_flag = true; }

  private:
    Orientation                             orientation;
    bool                                    destroy_flag;
    std::vector<Direction>                  directions;
    std::vector<Direction>::iterator        directions_it;
    double                                  distance_travelled;



    // AI Status (idle, passive, aggressive, defensive)
    // AI status 2 (idle, attacking, walking, running, grabbed,
};

#endif

