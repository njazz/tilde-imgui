
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
#include "pd_canvas.h"

#include "IUWindowController.hpp"

#include "PdCommonMenus.hpp"

#include "nfd.h"

#include "FileParser.h"

#include "Clipboard.h"

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

    Clipboard _clipboard;

public:
    AppController();

    PdPatchViewController* createNewPatchWindow();
    PdPatchViewController* createPatchWindowForExistingCanvas(xpd::CanvasPtr cnv);

    //
    void openFile(std::string f)
    {
        _serverProcess->post("open file: " + f);
        FileParser::open(f);
    }

    // ----------

    IUAction menuNew = IUAction([this] {

        createNewPatchWindow();

    });

    IUAction menuOpen = IUAction([this] {

        nfdchar_t* f = new nfdchar_t[1024];
        if (NFD_OpenDialog("pd", "~/", &f) == NFD_OKAY)
            openFile(std::string(f));
    });

    IUAction menuExit = IUAction([this] {
        for (auto w : _windowControllers) {
            //glfwSetWindowShouldClose(w->glWindow, 1);
            w->close();
        }
    });

    IUAction showConsoleWindow = IUAction([&]() {});

    void post(std::string s) { _serverProcess->post(s + "\n"); }

    IUAction newCanvasWindow = IUAction([&]() {

        auto p = std::shared_ptr<xpd::PdCanvas>((xpd::PdCanvas*)newCanvasWindow.userObject);//xpd::CanvasPtr(*(xpd::PdCanvas*)newCanvasWindow.userObject);//std::make_shared<xpd::PdCanvas>((xpd::PdCanvas*)newCanvasWindow.userObject);
        createPatchWindowForExistingCanvas(p);
    });
};

#endif /* AppController_hpp */
