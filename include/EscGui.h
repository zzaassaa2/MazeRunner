//
// Created by George Zorn on 3/20/21.
//

#ifndef MAZERUNNER_ESCGUI_H
#define MAZERUNNER_ESCGUI_H

#include "engine/scene/Gui.h"
class OpeningGui;

enum GuiType{
    Pause, Victory
};

class EscGui: public Gui {
public:
    GuiType type;
    double typeElapsed{0};
    explicit EscGui(GuiType typeIn);
    void render(Application &app) override;
};


#endif //MAZERUNNER_ESCGUI_H
