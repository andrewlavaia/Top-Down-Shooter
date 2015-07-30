
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
      Idle,       // Affects all entities. Set automatically whenever an entity is not moving, dying, or some other status. Plays Idle animation if available.
      Moving,     // Affects all entities. Set after entity is instructed to move. Plays Move animation if available.
      Die,        // Affects all entities. Set after entity's HP is reduced to 0. Plays Die animation if available. No collisions possible.
      Dead,       // Affects all entities. Set after entity's die animation has finished playing. Plays Dead animation if available. No collision possible.
      AttackingPrimary,   // Affects Weapon. Set after that weapon attacks. Plays PrimaryAttack animation if available.
      AttackingSecondary, // Affects Weapon. Set after that weapon attacks. Plays SecondaryAttack animation if available.
      Grabbing,   // Affects Hero. Set after Hero attempts to grab something. Plays Grabbing animation if available.
      Attacked,   // Affects Hero, NPC and Weapon. Set after entity takes damage. Plays Attacked animation if available.
      Grabbed,    // Affects NPC and Weapon. Set after Hero picks up entity. Plays Grabbed animation if available.
      Thrown,     // Affects NPC and Weapon. Set after Hero throws entity. Plays Thrown animation if available.
      Exited,     // Affects Hero and NPC. Set after collision with Exit Collidable. Currently does nothing.
      Impassable, // Affects Hero. Set after collision with impassable Collidable. Prevents movement and automatically moves entity back.
      Captured,   // Affects NPC. Set after collision with the SheepPen Collidable. Clears all directions.
    };

    AnimatedEntity(ParentType pType);
    virtual ~AnimatedEntity() {}

    virtual void                            collideWithEntity(const AnimatedEntity& a, sf::Time dt) = 0;
    virtual void                            playAnimation() = 0;

    virtual void                            Move();
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
    void                                    setOrientation(Orientation::Type t) { orientation.setType(t); }
    void                                    setOrientation(double d) { orientation.setType(d); }

    Orientation                             getOrientation() const { return orientation; }
    Orientation                             getRelativeOrientation(const AnimatedEntity& entity) const;
    double                                  getHP() const { return hitpoints; }
    double                                  getMaxHP() const { return max_hitpoints; }
    double                                  getSpeed() const { return speed; }
    double                                  getPower() const { return power; }
    Status                                  getStatus() const { return status; }
    ParentType                              getParentType() const { return parentType; }
    double                                  getScaleFactor() const { return scaleFactor; }
    bool                                    isCollisionOK() const { return collisionOK; }

    sf::Vector2f                            position;
    AnimatedSprite                          animatedSprite;
    sf::Sprite                              hitbox; // every animated entity should have an invisible sf::sprite behind it that will serve as a hitbox for collision tests
    sf::RectangleShape                      healthbar; //graphically displays current health
    sf::RectangleShape                      healthbar_damage; //graphically displays missing health

  protected:
    void                                    Destroy();
    void                                    TakeDamage(double damage);
    void                                    TakeDamageOverTime(double damage, sf::Time dt);

    void                                    clearDirections();
    void                                    setHitbox(const sf::Texture& texture, unsigned width, unsigned height);
    void                                    setHitPoints(double h) { hitpoints = h; }
    void                                    setMaxHitPoints(double h) { max_hitpoints = h; }
    void                                    setSpeed(double s) { speed = s; }
    void                                    setPower(double p) { power = p; }
    void                                    setScaleFactor(unsigned s) { scaleFactor = s; }

  private:
    ParentType                              parentType;
    Orientation                             orientation;
    double                                  hitpoints; // weapon durability, collidable destructibility
    double                                  max_hitpoints; // starting health
    double                                  speed;
    double                                  power;
    Status                                  status;
    std::vector<Direction>                  directions;
    std::vector<Direction>::iterator        directions_it;

    double                                  distance_travelled;
    double                                  scaleFactor;
    bool                                    collisionOK;

};

#endif

