#ifndef MOCK_APP_CONTROLLER_H
#define MOCK_APP_CONTROLLER_H

#include "AppController.hpp"

PdPatchViewController* AppController::createNewPatchWindow() { return 0; };

Preferences AppController::_preferences;
Preferences* AppController::preferences() { return &_preferences; };

AudioMIDISettings* AppController::_audioMIDISettings = 0;
AudioMIDISettings* AppController::audioMIDISettings() { return _audioMIDISettings; };

#endif // MOCK_APP_CONTROLLER_H
