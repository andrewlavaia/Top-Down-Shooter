
#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "gamestate.h"

class CIntroState : public CGameState
{
public:
	void Init(CGameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game, double interpolation);

	static CIntroState* Instance() {
		return &IntroState;
	}


protected:
	CIntroState()
  {
    fonts.load(Fonts::Calibri, "calibri.ttf");
  }

private:
	static CIntroState IntroState;

  ResourceHolder<sf::Font, Fonts::ID> fonts;
  ResourceHolder<sf::Texture, Textures::ID> textures;
  ResourceHolder<Animation, Animations::ID> animations;

  sf::Text header1;
  sf::Text header2;
  sf::Text header3;


};

#endif
