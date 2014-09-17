
#ifndef ORIENTATION_H
#define ORIENTATION_H

class Orientation
{
  public:
    enum Type {
      N,
      NE,
      E,
      SE,
      S,
      SW,
      W,
      NW,
    };

    Type getType() { return type; }
    void setType(Type t) { type = t; }

    Type getSlightLeft()
    {
      switch (type)
      {
        case N:
          return Orientation::NW;
          break;
        case NE:
          return Orientation::N;
          break;
        case E:
          return Orientation::NE;
          break;
        case SE:
          return Orientation::E;
          break;
        case S:
          return Orientation::SE;
          break;
        case SW:
          return Orientation::S;
          break;
        case W:
          return Orientation::SW;
          break;
        case NW:
          return Orientation::W;
          break;
      }
    }

    Type getSlightRight() {
      switch (type)
      {
        case N:
          return Orientation::NE;
          break;
        case NE:
          return Orientation::E;
          break;
        case E:
          return Orientation::SE;
          break;
        case SE:
          return Orientation::S;
          break;
        case S:
          return Orientation::SW;
          break;
        case SW:
          return Orientation::W;
          break;
        case W:
          return Orientation::NW;
          break;
        case NW:
          return Orientation::N;
          break;
      }
    }

  private:
      Type type;

};

#endif
