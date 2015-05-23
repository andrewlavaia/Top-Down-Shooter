#ifndef GUI_H
#define GUI_H

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widget.hpp>
#include <SFML/Graphics.hpp>

class GUI {
	public:
		virtual void Initialize() = 0;
		virtual void HandleEvent(sf::Event& event);
		virtual void Update();
		virtual void Render(sf::RenderWindow& window);

  protected:
    sfg::SFGUI m_sfgui; // Create an SFGUI. This is required before doing anything with SFGUI.
    sfg::Desktop desktop; // stores windows for sfgui
    sf::Clock clock; // needed to update desktop
};


#endif
