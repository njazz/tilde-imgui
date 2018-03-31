
//
//  AppController.hpp
//  imguiController
//
//  Created by Alex on 22/03/2018.
//

#ifndef AppController_hpp
#define AppController_hpp

#include "AppController.hpp"
#include "AppControllerBase.hpp"

#include "PdConsoleViewController.hpp"
#include "PdPatchViewController.hpp"

#include "pd_localprocess.h"
#include "pd_localserver.h"

#include "IUWindowController.hpp"

#include "menus/PdCommonMenus.hpp"

class AppConsoleObserver : public xpd::ConsoleObserver {
public:
    PdConsoleViewController* _logWindow = 0;

    virtual void update();
};

class AppController : public AppControllerBase {

    xpd::ServerSettings* _settings;
    xpd::PdLocalServer* _server;

    xpd::ProcessPtr _serverProcess;

    AppConsoleObserver _consoleObserver;

    PdCommonMenus _commonMenus;

public:
    AppController();

    void createNewPatchWindow();

    IUObserver menuNew = IUObserver([this] {

        createNewPatchWindow();

    });

    IUObserver menuExit = IUObserver([this] {
        for (auto w : _windowControllers) {
            glfwSetWindowShouldClose(w->glWindow, 1);
        }
    });
};

#endif /* AppController_hpp */
