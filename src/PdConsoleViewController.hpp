
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

#include "menus/PdConsoleMenu.hpp"

class PdConsoleViewController : public IUViewController {

    std::string _consoleText = "";
    bool _dspOn = false;

    // temporary
    bool _demoWindow = false;

    void _drawMenu();

public:
    PdConsoleViewController(PdCommonMenus*m) : _menu(m)
    {
        _menu.common->menuWindow.setAction(PdCommonWindowMenu::aClearConsole, &clearConsole);
        _menu.common->menuMedia.setAction(PdCommonMediaMenu::aDSPOn, &dspOn);
        _menu.common->menuMedia.setAction(PdCommonMediaMenu::aDSPOff, &dspOff);
        _menu.common->menuMedia.dspOn = &_dspOn;
    }

    xpd::PdLocalServer* pdServer = 0;
    xpd::ProcessPtr pdProcess = 0;

    PdConsoleMenu _menu;

    virtual void draw() override;

    void post(std::string line);

    virtual void setWindowController(IUWindowController* w) override;

    // -------

    IUObserver clearConsole = IUObserver([this](){
       _consoleText = "";
    });

    IUObserver dspOn = IUObserver([this](){
        _dspOn = true;
        pdProcess->dspSwitch(_dspOn);
    });

    IUObserver dspOff = IUObserver([this](){
        _dspOn = false;
        pdProcess->dspSwitch(_dspOn);
    });
};

#endif /* AppController_hpp */
