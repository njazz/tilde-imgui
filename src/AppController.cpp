
//
//  AppController.cpp
//  imguiController
//
//  Created by Alex on 22/03/2018.
//

#include "AppController.hpp"

void AppConsoleObserver::update()
{
    if (_logWindow) {
        _logWindow->post(text());
    }
}

AppController::AppController()
    : AppControllerBase()
{
    UIObjectFactory::registerAll();

    _settings = new xpd::ServerSettings("pd");
    _server = new xpd::PdLocalServer(*_settings);
    _serverProcess = _server->createProcess();
    _serverProcess->registerConsoleObserver(xpd::ConsoleObserverPtr(&_consoleObserver));

    PdConsoleViewController* vc = new PdConsoleViewController(&_commonMenus);
    vc->pdServer = _server;
    vc->pdProcess = _serverProcess;
    _consoleObserver._logWindow = vc;

    vc->_menu.common->menuFile.setAction(PdCommonFileMenu::aFileNew, &menuNew);
    vc->_menu.common->menuFile.setAction(PdCommonFileMenu::aFileExit, &menuExit);

    addWindow(new IUWindowController(vc, "Pd Console", 0, 100, 400, 600));

    _serverProcess->post("tilde~/imgui 0.01");

    _serverProcess->addSearchPath("/Users/njazz/Documents/tilde~/Libraries/");
    _serverProcess->loadLibrary("tilde~_imgui");


}

void AppController::createNewPatchWindow()
{
    PdPatchViewController* p = new PdPatchViewController(&_commonMenus);
    p->pdServer = _server;
    p->setPdProcess(_serverProcess);

    addWindow(new IUWindowController(p, "Patch", 300, 300, 640, 480));
}
