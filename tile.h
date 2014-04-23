
#ifndef TILE_H
#define TILE_H

#include<SFML/Graphics.hpp>


class Tile
{
public:
  Tile(int x_coord, int y_coord)
  {
    x = x_coord;
    y = y_coord;
  }
  int getX() { return x; }
  int getY() { return y; }
  sf::Sprite sprite;

private:
  int x;
  int y;
};

#endif
