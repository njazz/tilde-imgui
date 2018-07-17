#ifndef MOCK_CONSOLE_CONTROLLER_H
#define MOCK_CONSOLE_CONTROLLER_H

#include "PdConsoleViewController.hpp"

void PdConsoleViewController::post(std::string line)
{}

PdConsoleViewController::PdConsoleViewController(PdCommonMenus *m) : _menu(m)
{}

void PdConsoleViewController::setWindowController(IUWindowController *w){}
void PdConsoleViewController::draw() {}

void PdConsoleViewController::_clearConsole(){};
void PdConsoleViewController::_menuPreferences(){};
void PdConsoleViewController::_menuAudioSettings(){};
void PdConsoleViewController::_dspOn(){};
void PdConsoleViewController::_dspOff(){};



#endif // MOCK_CONSOLE_CONTROLLER_H
