
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

    void setType(Type t) { type = t; }
    void setType(double d);

    Type getType() { return type; }
    Type getSlightLeft();
    Type getSlightRight();
    Type getOppo();
    double getRotation();


  private:
      Type type;

};

#endif
