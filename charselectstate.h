
#ifndef CHARSELECTSTATE_H
#define CHARSELECTSTATE_H

#include "gamestate.h"

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


protected:
	CCharSelectState() { }

private:
	static CCharSelectState CharSelectState;

};

#endif
