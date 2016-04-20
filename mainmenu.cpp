#include "mainmenu.h"

MainMenu::MainMenu()
  : state(State::Menu)
{
  Initialize();
}

void MainMenu::Initialize()
{
	// Create a simple button and connect the click signal.
	auto button_ng = sfg::Button::Create( "New Game" );
	auto button_hs = sfg::Button::Create( "High Scores" );
  //auto button_options = sfg::Button::Create( "Options" );
	auto button_exit = sfg::Button::Create( "Exit" );


	button_ng->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &MainMenu::OnNGButtonClick, this ) );
	button_hs->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &MainMenu::OnHSButtonClick, this ) );
	//button_options->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &MainMenu::OnOptionsButtonClick, this ) );
	button_exit->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &MainMenu::OnExitButtonClick, this ) );

	// Create a vertical box layouter with 10 pixels spacing and add the label and button to it.
	auto box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 10.0f );
	box->Pack( button_ng, false );
	box->Pack( button_hs, false );
	//box->Pack( button_options, false );
	box->Pack( button_exit, false );

	box->SetPosition(sf::Vector2f(450, 250));

/*
	// Create a movable expandable window and add the box layouter to it. Also set the window's title.
	auto window = sfg::Window::Create();
	window->SetTitle( "Main Menu" );
	window->Add( box );
*/

	// Create a desktop and add the box directly (without a window)
	desktop.Add( box );

	clock.restart();
}

void MainMenu::OnNGButtonClick()
{
	state = MainMenu::Intro;
}

void MainMenu::OnHSButtonClick()
{
	state = MainMenu::HighScore;
}

/*
void MainMenu::OnOptionsButtonClick()
{
  state = MainMenu::Option;
}
*/

void MainMenu::OnExitButtonClick()
{
	state = MainMenu::Exit;
}
