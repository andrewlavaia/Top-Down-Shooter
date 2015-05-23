#include "mainmenu.h"

void MainMenu::Initialize()
{
	// Create the label.
	m_label = sfg::Label::Create( "Did this work?" );

	// Create a simple button and connect the click signal.
	auto button = sfg::Button::Create( "Click me" );
	button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &MainMenu::OnButtonClick, this ) );

	// Create a vertical box layouter with 5 pixels spacing and add the label
	// and button to it.
	auto box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );
	box->Pack( m_label );
	box->Pack( button, false );

	// Create a window and add the box layouter to it. Also set the window's title.
	auto window = sfg::Window::Create();
	window->SetTitle( "Main Menu" );
	window->Add( box );

	// Create a desktop and add the window to it.
	desktop.Add( window );
	clock.restart();
}

void MainMenu::OnButtonClick()
{
	m_label->SetText( "Can't believe this worked..." );
}
