
#include "orientation.h"

void Orientation::setType( double d )
{
  double x = 45/2;
  if( d <= x || d > 360 - x )
  {
    type = Orientation::N;
  }
  else if( d > x && d <= x*3 )
  {
    type = Orientation::NE;
  }
  else if( d > x*3 && d <= x*5 )
  {
    type = Orientation::E;
  }
  else if( d > x*5 && d <= x*7 )
  {
    type = Orientation::SE;
  }
  else if( d > x*7 && d <= x*9 )
  {
    type = Orientation::S;
  }
  else if( d > x*9 && d <= x*11 )
  {
    type = Orientation::SW;
  }
  else if( d > x*11 && d <= x*13 )
  {
    type = Orientation::W;
  }
  else if( d > x*13 && d <= x*15 )
  {
    type = Orientation::NW;
  }
}

Orientation::Type Orientation::getSlightLeft()
{
  switch( type )
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

Orientation::Type Orientation::getSlightRight() {
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

Orientation::Type Orientation::getOppo() {
  switch (type)
  {
    case N:
      return Orientation::S;
      break;
    case NE:
      return Orientation::SW;
      break;
    case E:
      return Orientation::W;
      break;
    case SE:
      return Orientation::NW;
      break;
    case S:
      return Orientation::N;
      break;
    case SW:
      return Orientation::NE;
      break;
    case W:
      return Orientation::E;
      break;
    case NW:
      return Orientation::SE;
      break;
  }
}

double Orientation::getRotation() {
  switch (type)
  {
    case N:
      return 0;
      break;
    case NE:
      return 45;
      break;
    case E:
      return 90;
      break;
    case SE:
      return 135;
      break;
    case S:
      return 180;
      break;
    case SW:
      return 225;
      break;
    case W:
      return 270;
      break;
    case NW:
      return 315;
      break;
  }
}

double Orientation::getOppoRotation()
{
  double d = ( static_cast<int>( getRotation() ) + 180 ) % 360; // need to cast to int for modulus operator
  return d;
}
