
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
#include <iostream>


class AnimatedEntity
{
  public:
    enum ParentType {
      HeroType,
      NPCType,
      WeaponType,
      CollidableType,
      ProjectileType
    };

    enum Status {
      Idle,
      Moving,
      Die,    // in process of becoming dead
      Dead,
      AttackingPrimary,
      AttackingSecondary,
      Grabbing,
      Throwing,
      Attacked, // getting attacked
      Grabbed, // getting grabbed
      Thrown, // getting thrown
    };

    AnimatedEntity(ParentType pType);
    virtual ~AnimatedEntity() {}

    virtual void                            collideWithEntity(const AnimatedEntity& a, sf::Time dt) = 0;
    virtual void                            playAnimation() = 0;

    void                                    Move();
    void                                    MoveOneUnit(Orientation::Type o, double speed, bool rotation = true);
    void                                    MoveOneUnit(double rotation, double speed);
    void                                    MoveAnimatedSprite(double interpolation);
    void                                    AddDirection(Orientation::Type orientation_type, double distance, double speed, bool rpt = false, double degrees = 0);
    void                                    AddDirectionOppo(double d);

    bool                                    checkCollision(const AnimatedEntity& a) const;
    bool                                    checkDistance(double distance, const AnimatedEntity& entity) const;
    bool                                    isDead() const;
    bool                                    isMoving() const { return !directions.empty(); }

    void                                    setStatus(Status s) { status = s; }

    Orientation                             getOrientation() const { return orientation; }
    Orientation::Type                       getRelativeOrientation(const AnimatedEntity& entity) const;
    double                                  getHP() const { return hitpoints; }
    double                                  getSpeed() const { return speed; }
    double                                  getPower() const { return power; }
    Status                                  getStatus() const { return status; }
    ParentType                              getParentType() const { return parentType; }
    double                                  getScaleFactor() const { return scaleFactor; }

    sf::Vector2f                            position;
    AnimatedSprite                          animatedSprite;
    sf::Sprite                              hitbox; // every animated entity should have an invisible sf::sprite behind it that will serve as a hitbox for collision tests

  protected:
    void                                    Destroy();
    void                                    TakeDamage(double damage);
    void                                    TakeDamageOverTime(double damage, sf::Time dt);

    void                                    setHitbox(const sf::Texture& texture, unsigned width, unsigned height);
    void                                    setHitPoints(double h) { hitpoints = h; }
    void                                    setSpeed(double s) { speed = s; }
    void                                    setPower(double p) { power = p; }
    void                                    setScaleFactor(unsigned s) { scaleFactor = s; }

  private:
    void                                    setOrientation(Orientation::Type t) { orientation.setType(t); }

    ParentType                              parentType;
    Orientation                             orientation;
    double                                  hitpoints; // ammo, weapon durability, collidable destructibility
    double                                  speed;
    double                                  power;
    Status                                  status;
    std::vector<Direction>                  directions;
    std::vector<Direction>::iterator        directions_it;
    double                                  distance_travelled;
    double                                  scaleFactor;
};

#endif

