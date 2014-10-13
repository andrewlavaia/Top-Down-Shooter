
#ifndef DIRECTION_H
#define DIRECTION_H

#include "orientation.h"

class Direction
{
  public:
    Direction (Orientation::Type t, double dist, double spd, bool rpt = true)
     {
        type = t;
        distance = dist;
        speed = spd;
        repeat = rpt;

        // avoid logic errors
        if(dist <=0 || spd <= 0)
       {
         //std::cout<<"Avoid negative distance or speed when creating Direction objects. Values each set to 1." <<std::endl;
         distance = 1;
         speed = 1;
       }
     }

    Orientation::Type getType() { return type; }
    unsigned getDistance() { return distance; }
    double getSpeed() { return speed; }
    bool isRepeat() { return repeat; }

  private:
    Orientation::Type type;
    double distance;
    double speed;
    bool repeat;
    //currentAnimation

};

#endif
