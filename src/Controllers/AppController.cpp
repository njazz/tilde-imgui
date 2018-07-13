
//
//  AppController.cpp
//  imguiController
//
//  Created by Alex on 22/03/2018.
//

#include "AppController.hpp"

#include "PdConsoleViewController.hpp"
#include "PdPatchViewController.hpp"

Preferences AppController::_preferences;
Preferences* AppController::preferences() { return &_preferences; };

AudioMIDISettings* AppController::_audioMIDISettings = 0;
AudioMIDISettings* AppController::audioMIDISettings() { return _audioMIDISettings; };

void AppConsoleObserver::update()
{
    if (_pdConsoleWindow) {
        _pdConsoleWindow->post(text());
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

    _audioMIDISettings = new AudioMIDISettings(_serverProcess);

    _pdConsoleViewController = new PdConsoleViewController(&_commonMenus);
    _pdConsoleViewController->pdServer = _server;
    _pdConsoleViewController->pdProcess = _serverProcess;
    _consoleObserver.setConsoleWindow(_pdConsoleViewController);

    _pdConsoleViewController->_menu.common->menuFile.setAction(PdCommonFileMenu::aFileNew, &menuNew);
    _pdConsoleViewController->_menu.common->menuFile.setAction(PdCommonFileMenu::aFileOpen, &menuOpen);
    _pdConsoleViewController->_menu.common->menuFile.setAction(PdCommonFileMenu::aFileQuit, &menuExit);

    addWindow(new IUWindowController(_pdConsoleViewController, "Pd Console", 0, 100, 400, 600));

    _serverProcess->post("tilde~/imgui 0.01");

    _serverProcess->addSearchPath("/Users/njazz/Documents/tilde~/Libraries/");
    _serverProcess->loadLibrary("tilde~_imgui");



    FileParser::setAppController(this);
}

PdPatchViewController* AppController::createNewPatchWindow()
{
    PdPatchViewController* p = new PdPatchViewController(&_commonMenus);
    p->pdServer = _server;
    p->setPdProcess(_serverProcess);
    p->data.clipboard = &_clipboard;

    p->addAction(PdPatchViewController::oNewCanvasWindow, &newCanvasWindow);

    addWindow(new IUWindowController(p, "Patch", 300, 300, 640, 480));

    return p;
}

PdPatchViewController* AppController::createPatchWindowForExistingCanvas(xpd::CanvasPtr cnv)
{
    PdPatchViewController* p = new PdPatchViewController(&_commonMenus);
    p->pdServer = _server;
    p->setPdProcess(_serverProcess, cnv);
    p->data.clipboard = &_clipboard;

    p->addAction(PdPatchViewController::oNewCanvasWindow, &newCanvasWindow);

    addWindow(new IUWindowController(p, "<Subpatch>", 320, 320, 640, 480));

    return p;
}

//

void AppController::openFile(std::string f)
{
    _serverProcess->post("open file: " + f);
    FileParser::open(f);
}

//
void AppController::_menuNew()
{
    createNewPatchWindow();
}

void AppController::_menuOpen()
{
    nfdchar_t* f = new nfdchar_t[1024];
    if (NFD_OpenDialog("pd", "~/", &f) == NFD_OKAY)
        openFile(std::string(f));
}

void AppController::_menuExit()
{
    for (auto w : _windowControllers) {
        //glfwSetWindowShouldClose(w->glWindow, 1);
        w->close();
    }
}

void AppController::_showConsoleWindow()
{
}

void AppController::_newCanvasWindow()
{
    auto p = std::shared_ptr<xpd::PdCanvas>((xpd::PdCanvas*)newCanvasWindow.userObject); //xpd::CanvasPtr(*(xpd::PdCanvas*)newCanvasWindow.userObject);//std::make_shared<xpd::PdCanvas>((xpd::PdCanvas*)newCanvasWindow.userObject);
    createPatchWindowForExistingCanvas(p);
}
