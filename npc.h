
#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "animatedentity.h"
#include "animation.h"
#include "animatedsprite.h"
#include "direction.h"


class DataTable;

class NPC : public AnimatedEntity
{
public:
  enum Type {
    Sheep,
    //BlackSheep,
    //RebelSheep,
    //PrizeSheep,
    McGinger,
    BigRick,
    UglyAmy,
    TooCoolJack,
    DeNiro,
    Barnaby,
    ToughSugar,
    AmbiguousAlex,
    BaldingSam,
    TypeCount
  };

  NPC(Type t, const ResourceHolder<Animation, Animations::ID>& animations, const DataTable& data, double x, double y);

  virtual void                            collideWithEntity(const AnimatedEntity& a, sf::Time dt);
  virtual void                            playAnimation();


private:
  Type                                    type;
  const Animation&                        idleAnimation;
  const Animation&                        moveAnimation;
  const Animation&                        dieAnimation;
  const Animation&                        deadAnimation;
  const Animation&                        attackedAnimation;
  const Animation&                        grabbedAnimation;
  const Animation&                        thrownAnimation;
};

#endif // NPC_H
