
#ifndef ANIMATEDENTITY_H
#define ANIMATEDENTITY_H

#include <typeinfo>
#include <SFML/Graphics.hpp>
#include "animatedsprite.h"
#include "animation.h"
#include "direction.h"
#include "resourceholder.h"
#include "collision.h"
#include "orientation.h" // MoveOppo()


class AnimatedEntity
{
  public:

    AnimatedEntity();
    virtual ~AnimatedEntity() {}

    sf::Vector2f                            position;
    AnimatedSprite                          animatedSprite;

    std::shared_ptr<Animation>              moveAnimation;
    std::shared_ptr<Animation>              deathAnimation;

    void                                    Move();
    void                                    MoveAnimatedSprite(double interpolation);
    void                                    AddDirection(Orientation::Type orientation_type, double distance, double speed, bool rpt = false);
    void                                    AddDirectionOppo(double d);

    virtual void                            collideWithEntity(const AnimatedEntity& a) = 0;

    virtual double getSpeed() { return 1; } // needed for NPCs

    void                                    setOrientation(Orientation::Type t) { orientation.setType(t); }
    Orientation                             getOrientation() const { return orientation; }
    Orientation::Type                       getRelativeOrientation(const AnimatedEntity& entity) const;

    bool                                    checkCollision(const AnimatedEntity& a) const;
    bool                                    checkDistance(double distance, const AnimatedEntity& entity) const;
    bool                                    isDestroyed() const { return destroy_flag; }
    bool                                    isNotMoving() const { return directions.empty(); }

    std::shared_ptr<Animation>              getCurrentAnimation() const { return currentAnimation; }
    void                                    setCurrentAnimation(std::shared_ptr<Animation> a) { currentAnimation = a; }

  protected:
    std::shared_ptr<Animation>              CreateAnimation(const sf::Texture& tex, unsigned width, unsigned height, unsigned sprite_count);
    void                                    Destroy();


  private:
    Orientation                             orientation;
    bool                                    destroy_flag;
    std::vector<Direction>                  directions;
    std::vector<Direction>::iterator        directions_it;
    double                                  distance_travelled;
    std::shared_ptr<Animation>              currentAnimation;




    // AI Status (idle, passive, aggressive, defensive)
    // AI status 2 (idle, attacking, walking, running, grabbed,
};

#endif

