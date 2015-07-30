
#ifndef CHARSELECTSTATE_H
#define CHARSELECTSTATE_H

#include "gamestate.h"
#include "animatedsprite.h"

class CCharSelectState : public CGameState
{
public:
	void Init(CGameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game, double interpolation);

	static CCharSelectState* Instance() {
		return &CharSelectState;
	}

  unsigned getSelectedHero() { return selectedHero; }



protected:
	CCharSelectState()
	{
    fonts.load(Fonts::Calibri, "calibri.ttf");

    textures.load(Textures::Human_1_SpriteSheet, "textures/human1.png");
    textures.load(Textures::Human_10_SpriteSheet, "textures/human10.png");
    textures.load(Textures::Human_11_SpriteSheet, "textures/human11.png");
    textures.load(Textures::Human_12_SpriteSheet, "textures/human12.png");

    animations.load( Animations::Human_1_Idle, textures.get( Textures::Human_1_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_10_Idle, textures.get( Textures::Human_10_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_11_Idle, textures.get( Textures::Human_11_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_12_Idle, textures.get( Textures::Human_12_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );

    hoverBorder.setSize( sf::Vector2f( 50, 50 ) );
    hoverBorder.setFillColor( sf::Color( 255, 50, 50, 100 ) );

    selectBorder.setSize( sf::Vector2f( 50, 50 ) );
    selectBorder.setFillColor( sf::Color( 50, 50, 255, 100 ) );

    selectedHero = 1;

	}

private:
	static CCharSelectState CharSelectState;

  ResourceHolder<sf::Font, Fonts::ID> fonts;
  ResourceHolder<sf::Texture, Textures::ID> textures;
  ResourceHolder<Animation, Animations::ID> animations;

  sf::Text header;

  AnimatedSprite hero1;
	AnimatedSprite hero2;
	AnimatedSprite hero3;
	AnimatedSprite hero4;

	sf::RectangleShape hoverBorder;
	sf::RectangleShape selectBorder;

	unsigned selectedHero;

};

#endif
