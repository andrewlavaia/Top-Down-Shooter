
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
    AnimatedEntity();
    virtual ~AnimatedEntity() {}

    sf::Vector2f                            position;
    AnimatedSprite                          animatedSprite;
    std::shared_ptr<Animation>              moveAnimation;
    std::shared_ptr<Animation>              deathAnimation;

    enum Status {
      Idle,
      Moving,
      Attacking,
      Thrown,
      Dead
    };

    void                                    Move();
    void                                    MoveOneUnit(Orientation::Type o, double speed);
    void                                    MoveAnimatedSprite(double interpolation);
    void                                    AddDirection(Orientation::Type orientation_type, double distance, double speed, bool rpt = false);
    void                                    AddDirectionOppo(double d);


    virtual void                            collideWithEntity(const AnimatedEntity& a, sf::Time dt) = 0;

    void                                    setOrientation(Orientation::Type t) { orientation.setType(t); }
    Orientation                             getOrientation() const { return orientation; }
    Orientation::Type                       getRelativeOrientation(const AnimatedEntity& entity) const;
    bool                                    checkCollision(const AnimatedEntity& a) const;
    bool                                    checkDistance(double distance, const AnimatedEntity& entity) const;
    bool                                    isDestroyed() const { return destroy_flag; }
    bool                                    isNotMoving() const { return directions.empty(); }
    std::shared_ptr<Animation>              getCurrentAnimation() const { return currentAnimation; }
    void                                    setCurrentAnimation(std::shared_ptr<Animation> a) { currentAnimation = a; }
    double                                  getHP() const { return hitpoints; }
    double                                  getSpeed() const { return speed; }
    double                                  getPower() const { return power; }

    //bool                                    canAttack();
    //void                                    reduceCoolDowns(sf::Time dt);
    //void                                    resetAttackCoolDown() { attack_cooldown = sf::seconds(attack_speed); }

    Status                                  getStatus() const { return status; }
    void                                    setStatus(Status s) { status = s; }

  protected:
    std::shared_ptr<Animation>              CreateAnimation(const sf::Texture& tex, unsigned width, unsigned height, unsigned sprite_count);
    void                                    Destroy();
    void                                    TakeDamage(double damage);
    void                                    TakeDamageOverTime(double damage, sf::Time dt);
    void                                    setSpeed(double s) { speed = s; }
    void                                    setPower(double p) { power = p; }

    //void                                    setAttackSpeed(double as) { attack_speed = as;}



  private:
    Orientation                             orientation;
    bool                                    destroy_flag;
    std::vector<Direction>                  directions;
    std::vector<Direction>::iterator        directions_it;
    double                                  distance_travelled;
    std::shared_ptr<Animation>              currentAnimation;
    double                                  hitpoints;
    double                                  speed; // affects movement speed and attack speed
    double                                  power;

    //double                                  attack_speed;
    //sf::Time                                attack_cooldown;

    Status                                  status;


    // AI demeanor (idle, passive, aggressive, defensive)
};

#endif

