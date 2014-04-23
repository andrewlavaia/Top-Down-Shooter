
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gamestate.h"
#include "level.h"

class CPlayState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CPlayState* Instance() {
		return &PlayState;
	}

protected:
	CPlayState() { }

private:
	static CPlayState PlayState;
	Level level;

};

#endif
