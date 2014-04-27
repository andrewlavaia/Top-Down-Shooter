
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "gamestate.h"

class CMenuState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game, double interpolation);

	static CMenuState* Instance() {
		return &MenuState;
	}


protected:
	CMenuState() { }

private:
	static CMenuState MenuState;


};

#endif
