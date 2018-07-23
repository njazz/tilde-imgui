//

#include "IUMainMenuBase.hpp"

#include "PdCommonMenus.hpp"

class PdConsoleMenu : public IUMainMenuBase {
public:
    PdCommonMenus* common = 0;
    //    PdCommonFileMenu menuFile;
    //    PdCommonWindowMenu menuWindow;
    //    PdCommonMediaMenu menuMedia;

    PdConsoleMenu(PdCommonMenus* m)
    {
        if (!m) return;

        common = m;
        addMenu(&m->menuFile, "File");
        addMenu(&m->menuWindow, "Window");
        addMenu(&m->menuMedia, "Media");
        addMenu(&m->menuHelp, "Help");
    }
};
