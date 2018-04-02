
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

#include "nfd.h"

class AppConsoleObserver : public xpd::ConsoleObserver {
    PdConsoleViewController* _pdConsoleWindow = 0;

public:
    void setConsoleWindow(PdConsoleViewController* w) { _pdConsoleWindow = w; };

    virtual void update();
};

class AppController : public AppControllerBase {

    xpd::ServerSettings* _settings;
    xpd::PdLocalServer* _server;

    xpd::ProcessPtr _serverProcess;

    AppConsoleObserver _consoleObserver;

    PdCommonMenus _commonMenus;

    PdConsoleViewController* _pdConsoleViewController = 0;

public:
    AppController();

    void createNewPatchWindow();

    //
    void openFile(std::string f)
    {
        _serverProcess->post("open file: " + f);
    }

    // ----------

    IUObserver menuNew = IUObserver([this] {

        createNewPatchWindow();

    });

    IUObserver menuOpen = IUObserver([this] {

        nfdchar_t* f = new nfdchar_t[1024];
        if (NFD_OpenDialog("", "~/", &f) == NFD_OKAY)
            openFile(std::string(f));
    });

    IUObserver menuExit = IUObserver([this] {
        for (auto w : _windowControllers) {
            glfwSetWindowShouldClose(w->glWindow, 1);
        }
    });

    IUObserver showConsoleWindow = IUObserver([this] {});
};

#endif /* AppController_hpp */
