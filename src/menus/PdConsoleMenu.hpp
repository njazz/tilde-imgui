//

#include "IUMainMenuBase.hpp"

#include "PdCommonMenus.hpp"


class PdConsoleMenu : public IUMainMenuBase {
public:
    PdCommonFileMenu menuFile;
    PdCommonWindowMenu menuWindow;
    PdCommonMediaMenu menuMedia;

    PdConsoleMenu()
    {
        addMenu(&menuFile, "File");
        addMenu(&menuWindow, "Window");
        addMenu(&menuMedia, "Media");
    }
};
