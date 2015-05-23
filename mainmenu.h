#ifndef MAINMENU_H
#define MAINMENU_H

#include "gui.h"

class MainMenu : public GUI {
  public:
    void Initialize();

	private:
    void OnButtonClick(); // button click handler

    sfg::Label::Ptr m_label; // Create the label pointer here to reach it from OnButtonClick().

};


#endif
