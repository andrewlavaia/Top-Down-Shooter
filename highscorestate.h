
#ifndef HIGHSCORESTATE_H
#define HIGHSCORESTATE_H

#include "gamestate.h"

class CHighScoreState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CHighScoreState* Instance() {
		return &HighScoreState;
	}

protected:
	CHighScoreState() { }

private:
	static CHighScoreState HighScoreState;

};

#endif
