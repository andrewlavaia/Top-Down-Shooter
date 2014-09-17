
#include "weapon.h"

Weapon::Weapon(Type t)
  : attack1(Attack::Push), // default initialization
    attack2(Attack::Push)  // default initialization
{
  type = t;
  durability = 5;
  position.x = rand()%1024;    //random number generator : rand()%(max-min+1) + min
  position.y = rand()%768;

  sf::Texture texture;
  texture.create(10,10);
  sprite.setTexture(texture); // aassign empty texture 20x20 pixels
  sprite.setColor(sf::Color(255,0,0,100)); // semi-transparent red hitbox
  sprite.setOrigin(5, 5);
  sprite.setPosition(position.x,position.y);

  switch(type)
  {
    case Weapon::Hands :
      attack_modifier = 1;
      attack1.setType(Attack::Grab);
      attack2.setType(Attack::Push);
      break;

    case Weapon::Pole :
      attack_modifier = 2;
      attack1.setType(Attack::Push);
      attack2.setType(Attack::Push);
  }

}

/*
void Weapon::Grab(Hero& hero, std::unique_ptr<NPC>& npc)
{
  // Animate hands

  // pick up npc
  //npc->position.x = hero.position.x;
  //npc->position.y = hero.position.y;
  npc->animatedSprite.rotate(90);
  npc->animatedSprite.hitbox.rotate(90);
}
*/
