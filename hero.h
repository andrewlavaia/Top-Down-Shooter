#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>

class Hero
{
public:
  Hero();

  double x;
  double y;

  sf::Texture texture;
  sf::Sprite sprite;

  double speed;
  double velocity;


private:



};



#endif // HERO_H
