#include "gameengine.h"
#include "menustate.h"
#include "timer.h"



int main()
{
  // Create main window
  sf::RenderWindow window;
  window.create(sf::VideoMode(1024, 768), "Subway Mercenary", sf::Style::Default);

  // Set window settings
  // window.setFramerateLimit(60);

  // Create the game engine with window (stores a reference)
  CGameEngine game(window);

  // Initialize game and start game at Main Menu
	game.Init();
	game.PushState(CMenuState::Instance());

  double frame_length = 1000/60;

  // Main game loop
	while (game.Running())
	{
    game.timer.StartCounter();
    game.HandleEvents();
    game.Update();
    if(game.render_timer.GetCounter() >= frame_length)
    {
      game.Draw();
      std::cout << "Rendered in: " << game.render_timer.GetCounter()<< std::endl;
      game.render_timer.StartCounter();
    }
    std::cout << "Main Game Loop: " << game.timer.GetCounter()<<std::endl;
	}

  // cleanup the engine
	game.Cleanup();

  return 0;
}
