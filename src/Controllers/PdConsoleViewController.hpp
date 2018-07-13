
//
//  AppController.hpp
//  imguiController
//
//  Created by Alex on 22/03/2018.
//

#ifndef PdConsoleViewController_hpp
#define PdConsoleViewController_hpp

#include "IUViewController.hpp"
#include "imgui.h"

#include "pd_localprocess.h"
#include "pd_localserver.h"

#include "IUWindowController.hpp"

#include "PdConsoleMenu.hpp"

#include "UIPropertiesWindow.hpp"

class PdConsoleViewController : public IUViewController {

    std::string _consoleText = "";
    bool _dspState = false;

    // temporary
    bool _demoWindow = false;

    void _drawMenu();

    char* _buf = new char[255];

    UIPropertiesWindow _preferencesWindow ;
    bool _displayPreferences = false;
public:
    PdConsoleViewController(PdCommonMenus* m);

    xpd::PdLocalServer* pdServer = 0;
    xpd::ProcessPtr pdProcess = 0;

    PdConsoleMenu _menu;

    virtual void draw() override;

    void post(std::string line);

    virtual void setWindowController(IUWindowController* w) override;

    // -------

    IU_ACTION(clearConsole);
    IU_ACTION(dspOn);
    IU_ACTION(dspOff);

    IU_ACTION(menuPreferences);

};

#endif /* AppController_hpp */
