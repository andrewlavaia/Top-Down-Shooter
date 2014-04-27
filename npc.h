
#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>

class NPC
{
public:
  NPC();

  void MoveSprite(double interpolation);        // Animates sprite towards its new location based on time factor

  sf::Vector2f position;

  sf::Texture texture;
  sf::Sprite sprite;

  double speed;
  double weight;

private:

};


#endif // NPC_H
