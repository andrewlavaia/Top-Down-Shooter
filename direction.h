
#ifndef DIRECTION_H
#define DIRECTION_H

#include "orientation.h"

class Direction
{
  public:
    Direction (Orientation::Type t, double d, double s, bool r = true)
     {
       type = t;
       distance = d;
       speed = s;
       repeat = r;
     }

    Orientation::Type getType() { return type; }
    double getDistance() { return distance; }
    double getSpeed() { return speed; }
    bool isRepeat() { return repeat; }

  private:
    Orientation::Type type;
    double distance;
    double speed;
    bool repeat;
    Animation* animation;
    //currentAnimation

};

#endif
