
#ifndef HIGHSCORESTATE_H
#define HIGHSCORESTATE_H

#include "gamestate.h"

class CHighScoreState : public CGameState
{
public:
	void Init(CGameEngine* game);
	void Cleanup();

	void Pause(CGameEngine* game);
	void Resume(CGameEngine* game);

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game, double interpolation);

	static CHighScoreState* Instance() {
		return &HighScoreState;
	}

protected:
	CHighScoreState()
	{
    fonts.load(Fonts::Calibri, "calibri.ttf");
  }

private:
	static CHighScoreState HighScoreState;

  ResourceHolder<sf::Font, Fonts::ID> fonts;
  ResourceHolder<sf::Texture, Textures::ID> textures;
  ResourceHolder<Animation, Animations::ID> animations;

  sf::Text header;

};

#endif
