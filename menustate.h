
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "gamestate.h"
#include "mainmenu.h"

class CMenuState : public CGameState
{
public:
	void Init(CGameEngine* game);
	void Cleanup();

	void Pause(CGameEngine* game);
	void Resume(CGameEngine* game);

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game, double interpolation);

	static CMenuState* Instance() {
		return &MenuState;
	}

	MainMenu menu;

protected:
	CMenuState() { }

private:
	static CMenuState MenuState;


};

#endif
