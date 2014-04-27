
#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>

class Hero
{
public:
  Hero();

  void MoveSprite(double interpolation);   // Animates sprite towards its new location based on time factor

  sf::Vector2f position;

  sf::Texture texture;
  sf::Sprite sprite;

  double speed;
  double strength;


private:


};



#endif // HERO_H
