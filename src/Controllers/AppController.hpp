
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

#include "pd_localprocess.h"
#include "pd_localserver.h"
#include "pd_canvas.h"

#include "IUWindowController.hpp"

#include "PdCommonMenus.hpp"

#include "Clipboard.h"

#include "Preferences.h"
#include "AudioMIDISettings.h"

class PdConsoleViewController;
class PdPatchViewController;

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
    PdConsoleViewController* _pdConsoleViewController = 0;

    PdCommonMenus _commonMenus;

    Clipboard _clipboard;

    static Preferences _preferences;
    static AudioMIDISettings* _audioMIDISettings;

    static ImFont* _fixedWidthFont;
public:
    AppController();

    PdPatchViewController* createNewPatchWindow();
    PdPatchViewController* createPatchWindowForExistingCanvas(xpd::CanvasPtr cnv);

    //
    void openFile(std::string f);

    // ----------

    IU_ACTION(menuNew);
    IU_ACTION(menuOpen);
    IU_ACTION(menuExit);

    /// \todo show console window action
    IU_ACTION(showConsoleWindow);

    IU_ACTION(newCanvasWindow);

    IU_ACTION(openHelpPatch);

    void post(std::string s) { _serverProcess->post(s + "\n"); }

    static Preferences* preferences();
    static AudioMIDISettings* audioMIDISettings();

    //
    static ImFont* fixedWidthFont(){return _fixedWidthFont;};
};

#endif /* AppController_hpp */
