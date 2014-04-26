
#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>

class NPC
{
public:
  NPC();

  double x;
  double y;

  sf::Texture texture;
  sf::Sprite sprite;

  double speed;
  double velocity;
  bool collision_flag;

private:



};



#endif // NPC_H
