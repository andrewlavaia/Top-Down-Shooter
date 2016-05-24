
#include "gameengine.h"
#include "gamestate.h"

CGameEngine::CGameEngine(sf::RenderWindow &sfmlwindow)
: window(sfmlwindow),
  isPaused(false)
{

}
void CGameEngine::Init()
{
	running = true;
	timer.StartCounter();
	tick_timer.StartCounter();

	frameTime = sf::Time::Zero;
	logicTime = sf::Time::Zero;

	if(!font.loadFromFile("calibri.ttf"))
  {
    //throw exception...
    std::cout<<"Font Not Loaded"<<std::endl;
  }

}

void CGameEngine::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// Close Window
	window.close();

}

void CGameEngine::ChangeState(CGameState* state)
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void CGameEngine::PushState(CGameState* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause(this);
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void CGameEngine::PopState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume(this);
	}
}


void CGameEngine::HandleEvents()
{
	// let the state handle events
	states.back()->HandleEvents(this);
}

void CGameEngine::Update()
{
	// let the state update the game
	states.back()->Update(this);
}

void CGameEngine::Draw(double interpolation)
{
	// let the state draw the screen
	states.back()->Draw(this, interpolation);
}
