#ifndef MAINMENU_H
#define MAINMENU_H

#include "gui.h"

class MainMenu : public GUI {
  public:
    enum State {
      Menu,
      Intro,
      HighScore,
      Option,
      Exit
    };

    MainMenu();
    void Initialize();
    State getState() const { return state; }

	private:
	  State state;

    void OnNGButtonClick(); // new game button click handler
    void OnHSButtonClick(); // high score button click handler
    void OnOptionsButtonClick(); // options button click handler
    void OnExitButtonClick(); // exit button click handler


};


#endif
