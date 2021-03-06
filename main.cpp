#include <SFGUI/SFGUI.hpp>
#include "gameengine.h"
#include "menustate.h"
#include "timer.h"

int main()
{
  // Create main window
  sf::RenderWindow window;
  window.create(sf::VideoMode(1024, 768), "Sheep Herder", sf::Style::Default);

  // Create the game engine with window (stores a reference)
  CGameEngine game(window);

  // Initialize game and start game at Main Menu
	game.Init();
	game.PushState(CMenuState::Instance());

  // Set Game loop variables
  const int TICKS_PER_SECOND = 25; // how often game is updated (logic, physics, input checking)
  const int TIME_PER_TICK = 1000/TICKS_PER_SECOND;
  double next_game_tick = 0;
  double interpolation = 0;

  // Fixed game loop with variable FPS
	while (game.Running())
	{
    game.timer.StartCounter();
    game.frameTime = game.frameClock.restart();

    while(game.tick_timer.GetCounter() > next_game_tick)
    {
      game.HandleEvents();

      if(!game.isPaused)
        game.Update();

      next_game_tick += TIME_PER_TICK;
      game.logicTime = game.logicClock.restart();
    }
    interpolation = (game.tick_timer.GetCounter() - next_game_tick + TIME_PER_TICK ) / TIME_PER_TICK;
    game.Draw(interpolation);
}

  // cleanup the engine
	game.Cleanup();

  return 0;
}
