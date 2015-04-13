
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gamestate.h"
#include "level.h"
#include "hero.h"

class CPlayState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game, double interpolation);

	static CPlayState* Instance() {
		return &PlayState;
	}

  bool noKeyPressed;

protected:
	CPlayState()
	{
	  hero = std::make_shared<Hero>();
	  level = std::make_shared<Level>(1, hero);
  }

private:
	static CPlayState PlayState;

  std::shared_ptr<Hero> hero;
	std::shared_ptr<Level> level;

};

#endif
