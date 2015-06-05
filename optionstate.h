
#ifndef OPTIONSTATE_H
#define OPTIONSTATE_H

#include "gamestate.h"

class COptionState : public CGameState
{
public:
	void Init(CGameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game, double interpolation);

	static COptionState* Instance() {
		return &OptionState;
	}

protected:
	COptionState() { }

private:
	static COptionState OptionState;

};

#endif
