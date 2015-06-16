
#ifndef DIRECTION_H
#define DIRECTION_H

#include "orientation.h"
#include <cassert>
#include <iostream>

class Direction
{
  public:
  Direction( Orientation::Type t, double dist, double spd, bool rpt = true, double degrees = 0 )
    : type( t ),
      rotation( degrees ),
      distance( dist ),
      speed( spd ),
      repeat( rpt )
  {

    // avoid logic errors
    assert( dist >= 0 && spd >= 0 );

    if( dist == 0 || spd == 0 )
    {
      distance = .01;
      speed = .01;
    }
  }

    Orientation::Type getType() const { return type; }
    double getRotation() const { return rotation; }
    double getDistance() const { return distance; }
    double getSpeed() const { return speed; }
    bool isRepeat() const { return repeat; }

  private:
    Orientation::Type type;
    double rotation;
    double distance;
    double speed;
    bool repeat;

};

#endif
