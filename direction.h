
#ifndef DIRECTION_H
#define DIRECTION_H

class Direction
{
  public:
    enum Type {
      Up,
      Down,
      Left,
      Right,
      Up_Left,
      Up_Right,
      Down_Left,
      Down_Right,
      Pause,
    };

    Direction (Type t, float d)
     {
       type = t;
       distance = d;
     }

    float getDistance() { return distance; }
    Type getType() { return type; }

  private:
    Type type;
    float distance;
};

#endif
