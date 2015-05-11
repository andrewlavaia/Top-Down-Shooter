
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
      Attacking,
      Grabbing,
      Throwing,
      Attacked, // getting attacked
      Grabbed, // getting grabbed
      Thrown, // getting thrown
    };

    AnimatedEntity(ParentType pType);
    virtual ~AnimatedEntity() {}

    sf::Vector2f                            position;
    AnimatedSprite                          animatedSprite;

    virtual void                            collideWithEntity(const AnimatedEntity& a, sf::Time dt) = 0;
    virtual void                            playAnimation() = 0;

    void                                    Move();
    void                                    MoveOneUnit(Orientation::Type o, double speed, bool rotation = true);
    void                                    MoveAnimatedSprite(double interpolation);
    void                                    AddDirection(Orientation::Type orientation_type, double distance, double speed, bool rpt = false);
    void                                    AddDirectionOppo(double d);

    void                                    setOrientation(Orientation::Type t) { orientation.setType(t); }
    void                                    setStatus(Status s) { status = s; }

    bool                                    checkCollision(const AnimatedEntity& a) const;
    bool                                    checkDistance(double distance, const AnimatedEntity& entity) const;
    bool                                    isDead() const;
    bool                                    isMoving() const { return !directions.empty(); }

    Orientation                             getOrientation() const { return orientation; }
    Orientation::Type                       getRelativeOrientation(const AnimatedEntity& entity) const;
    double                                  getHP() const { return hitpoints; }
    double                                  getSpeed() const { return speed; }
    double                                  getPower() const { return power; }
    Status                                  getStatus() const { return status; }
    ParentType                              getParentType() const { return parentType; }

    // every animated entity should have an invisible sf::sprite behind it that will serve as a hitbox for collision tests
    sf::Sprite hitbox;
    void setHitbox(const sf::Texture& texture, int width, int  height);


  protected:
    std::shared_ptr<Animation>              CreateAnimation(const sf::Texture& tex, unsigned width, unsigned height, unsigned sprite_count);
    void                                    Destroy();
    void                                    TakeDamage(double damage);
    void                                    TakeDamageOverTime(double damage, sf::Time dt);
    void                                    setHitPoints(double h) { hitpoints = h; }
    void                                    setSpeed(double s) { speed = s; }
    void                                    setPower(double p) { power = p; }

  private:
    ParentType                              parentType;
    Orientation                             orientation;
    std::vector<Direction>                  directions;
    std::vector<Direction>::iterator        directions_it;
    double                                  distance_travelled;
    double                                  hitpoints; // ammo, weapon durability, collidable destructibility
    double                                  speed;
    double                                  power;
    Status                                  status;


    // AI demeanor (idle, passive, aggressive, defensive)
};

#endif

