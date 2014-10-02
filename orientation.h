
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

    Type getSlightLeft();
    Type getSlightRight();
    Type getOppo();

    double getRotation();


  private:
      Type type;

};

#endif
