
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
	CIntroState() { }

private:
	static CIntroState IntroState;

};

#endif
