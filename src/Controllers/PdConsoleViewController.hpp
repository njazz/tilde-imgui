
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

class PdConsoleViewController : public IUViewController {

    std::string _consoleText = "";
    bool _dspOn = false;

    // temporary
    bool _demoWindow = false;

    void _drawMenu();

public:
    PdConsoleViewController(PdCommonMenus* m);

    xpd::PdLocalServer* pdServer = 0;
    xpd::ProcessPtr pdProcess = 0;

    PdConsoleMenu _menu;

    virtual void draw() override;

    void post(std::string line);

    virtual void setWindowController(IUWindowController* w) override;

    // -------

    IUAction clearConsole = IUAction([this]() {
        _consoleText = "";
    });

    IUAction dspOn = IUAction([this]() {
        _dspOn = true;
        pdProcess->dspSwitch(_dspOn);
    });

    IUAction dspOff = IUAction([this]() {
        _dspOn = false;
        pdProcess->dspSwitch(_dspOn);
    });
};

#endif /* AppController_hpp */
