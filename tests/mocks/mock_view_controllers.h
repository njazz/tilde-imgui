#ifndef MOCK_VIEW_CONTROLLERS_H
#define MOCK_VIEW_CONTROLLERS_H

#include "AppController.hpp"

#include "PdPatchViewController.hpp"

// ** TODO: split this

// !! **** IUAction
IUAction::IUAction(std::function<void ()> fn){
    _callback = fn;
}

// ******* prefs
Preferences::Preferences() {}

// ******* grid
Grid::Grid() {}
void Grid::_drawContents() {}

// ******* undo stack
UndoStack::UndoStack(){}



// ******* new connection
void NewConnection::draw() {}

// ******* appcontroller
PdPatchViewController* AppController::createNewPatchWindow() { return 0; };

Preferences AppController::_preferences;
Preferences* AppController::preferences() { return &_preferences; };

AudioMIDISettings* AppController::_audioMIDISettings = 0;
AudioMIDISettings* AppController::audioMIDISettings() { return _audioMIDISettings; };

// *******  patch controller

PdPatchViewController::PdPatchViewController(PdCommonMenus* m)
    : _patchMenu(m)
    , _preferencesWindow(AppController::preferences(), &displayPreferences)
    , _audioSettingsWindow(AppController::audioMIDISettings(), &displayAudioSettings){};

void PdPatchViewController::connectObjectsByIndices(int, int, int, int){};
void PdPatchViewController::resizeContentsToObjects(){};
void PdPatchViewController::loadbang(){};

void PdPatchViewController::draw(){};
void PdPatchViewController::_drawContents(){};
void PdPatchViewController::drawMenu(){};

void PdPatchViewController::onMouseDown(ImVec2 pos){};
void PdPatchViewController::onMouseDoubleClick(ImVec2 pos){};
void PdPatchViewController::onMouseDrag(ImVec2 pos){};
void PdPatchViewController::onMouseUp(ImVec2 pos){};
void PdPatchViewController::onMouseHover(ImVec2 pos){};


#define MOCK_ACTION(x) void PdPatchViewController::_##x(){}

MOCK_ACTION(autocomplete)
MOCK_ACTION(objectUpdated)
MOCK_ACTION(objectCreated)
MOCK_ACTION(outletClicked)
MOCK_ACTION(inletHovered)
MOCK_ACTION(inletClicked)

MOCK_ACTION(openCanvas)
MOCK_ACTION(showHelpPatch);

MOCK_ACTION(menuSaveAction)
MOCK_ACTION(menuSaveAsAction)

MOCK_ACTION(menuCutAction);
MOCK_ACTION(menuCopyAction);
MOCK_ACTION(menuPasteAction);
MOCK_ACTION(menuSelectAllAction);
MOCK_ACTION(menuDeleteObjectAction);

MOCK_ACTION(editModeAction);

MOCK_ACTION(menuPreferences);
MOCK_ACTION(menuAudioSettings);

MOCK_ACTION(arrangeDHAction);
MOCK_ACTION(arrangeDVAction);

MOCK_ACTION(arrangeLeftAction);
MOCK_ACTION(arrangeCenterAction);
MOCK_ACTION(arrangeRightAction);
MOCK_ACTION(arrangeTopAction);
MOCK_ACTION(arrangeBottomAction);

MOCK_ACTION(zoomIn);
MOCK_ACTION(zoomOut);
MOCK_ACTION(zoomOne);

MOCK_ACTION(putObject);
MOCK_ACTION(putMessage);
MOCK_ACTION(putComment);

MOCK_ACTION(putBang);
MOCK_ACTION(putToggle);
MOCK_ACTION(putNumber);


// ******* common menus
PdPatchMenu::PdPatchMenu(PdCommonMenus*){};

void PdCommonFileMenu::_drawContents() {}
void PdCommonHelpMenu::_drawContents() {}
void PdCommonMediaMenu::_drawContents() {}
void PdCommonWindowMenu::_drawContents() {}

void PdCommonFileMenu::_shortcutContents() {}
//void PdCommonHelpMenu::_shortcutContents(){}
void PdCommonMediaMenu::_shortcutContents() {}
void PdCommonWindowMenu::_shortcutContents() {}

// ******* patch menus
void PdPatchArrangeMenu::_drawContents(){};
void PdPatchEditMenu::_drawContents(){};
void PdPatchPutMenu::_drawContents(){};

void PdPatchArrangeMenu::_shortcutContents(){};
void PdPatchEditMenu::_shortcutContents(){};
void PdPatchPutMenu::_shortcutContents(){};

// ******* object base

UiObjectBase* PdPatchViewController::createObject(std::string text, int x, int y){return 0;}

// ******* object
void UIObject::draw(){};
void UIObject::drawObjectContents(){};

#endif // MOCK_VIEW_CONTROLLERS_H
