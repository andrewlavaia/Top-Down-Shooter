#include "gui.h"

void GUI::HandleEvent(sf::Event& event)
{
  desktop.HandleEvent(event);
}

void GUI::Update()
{
  desktop.Update( clock.restart().asSeconds() );
}

void GUI::Render(sf::RenderWindow& window)
{
  m_sfgui.Display( window );
}


