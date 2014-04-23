
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp> // OpenGL for antialiasing
#include <vector>
#include "timer.h"

class CGameState;

class CGameEngine
{
public:
  CGameEngine(sf::RenderWindow &sfmlwindow);
  void Init();
	void Cleanup();

	void ChangeState(CGameState* state);
	void PushState(CGameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return running; }
	void Quit() { running = false; }

	sf::RenderWindow& window;
  Timer timer;
  Timer render_timer;

private:
	// the stack of states
	std::vector<CGameState*> states;
	bool running;
};

#endif
