
//
//  AppController.cpp
//  imguiController
//
//  Created by Alex on 22/03/2018.
//

#include "AppController.hpp"

#include "PdConsoleViewController.hpp"

int consoleInputCallback(ImGuiTextEditCallbackData* data)
{
    PdConsoleViewController* vc = (PdConsoleViewController*)data->UserData;
    vc->windowController()->isEditingText = true;
    //vc->windowController()->restoreContext();

    return 0;
}

PdConsoleViewController::PdConsoleViewController(PdCommonMenus* m)
    : _menu(m), _preferencesWindow(AppController::preferences(), &_displayPreferences)
    ,_audioSettingsWindow(AppController::audioMIDISettings(), &_displayAudioSettings)
{
    _menu.common->menuWindow.setAction(PdCommonWindowMenu::aClearConsole, &clearConsole);
    _menu.common->menuMedia.setAction(PdCommonMediaMenu::aDSPOn, &dspOn);
    _menu.common->menuMedia.setAction(PdCommonMediaMenu::aDSPOff, &dspOff);
    _menu.common->menuMedia.dspOn = &_dspState;

    _menu.common->menuWindow.setAction(PdCommonWindowMenu::aSettings,&menuPreferences);
    _menu.common->menuWindow.setAction(PdCommonWindowMenu::aAudioMIDI,&menuAudioSettings);
}

void PdConsoleViewController::_drawMenu()
{
    _menu.setWindowController(windowController());
    _menu.common->setWindowController(windowController());
    _menu.draw();
}

void PdConsoleViewController::draw()
{
    // todo: use _drawContents()

    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::SetNextWindowPos(ImVec2(0, 22));

    bool w = true;
    ImGui::Begin("pd_console", &w, ImVec2(0, 0), 0.75, ImGuiWindowFlags_NoTitleBar);

    _drawMenu();

    ImGui::Text("Log level:");
    ImGui::SameLine();

    ImGui::PushItemWidth(150);
    if (ImGui::BeginCombo("", "2 normal")) {
        ImGui::MenuItem("0 fatal");
        ImGui::MenuItem("1 error");
        ImGui::MenuItem("2 normal");
        ImGui::MenuItem("3 debug");
        ImGui::MenuItem("4 all");

        ImGui::EndCombo();
    }
    ImGui::SameLine(270);
    ImGui::Text("%i FPS", (int)ImGui::GetIO().Framerate);
    ImGui::SameLine();

    _dspState = pdProcess->dspState();

    if (ImGui::Checkbox("DSP", &_dspState)) {
        pdProcess->dspSwitch(_dspState);
    }

    ImGui::Separator();

    ImGui::Text(";");
    ImGui::SameLine();
    if (ImGui::InputText(" ", _buf, 255, ImGuiInputTextFlags_EnterReturnsTrue, &consoleInputCallback, (void*)this)) {
        windowController()->isEditingText = false;
        windowController()->restoreContext();

        std::string send = _buf;

        std::string obj, msg;

        auto pos = send.find(' ', 0);

        _buf[0] = '\0';
        if (pdProcess && pos != std::string::npos) {
            msg = send.substr(pos + 1);
            obj = send.substr(0, pos);
            //pdProcess->post("out: "+obj+":"+msg+"\n");
            pdProcess->sendMessage(obj, msg);
        }
    }

    ImGui::SameLine();

    ImGui::Text("ImGui:");
    ImGui::SameLine();
    ImGui::Checkbox("Metrics", &_demoWindow);
    if (_demoWindow) {
        ImGui::SetNextWindowSize(ImVec2(300, 400));
        ImGui::ShowMetricsWindow(); //&_demoWindow);
    }

    ImGui::Separator();

    ImGui::Text("%s", _consoleText.c_str());

    ImGui::End();

    _preferencesWindow._drawContents();
    _audioSettingsWindow._drawContents();
};

void PdConsoleViewController::post(std::string line)
{
    _consoleText = line + _consoleText;
}

void PdConsoleViewController::setWindowController(IUWindowController* w)
{
    IULayer::setWindowController(w);
    _menu.setWindowController(w);
};

//

void PdConsoleViewController::_clearConsole()
{
    _consoleText = "";
};

void PdConsoleViewController::_dspOn()
{
    _dspState = true;
    pdProcess->dspSwitch(_dspState);
};

void PdConsoleViewController::_dspOff()
{
    _dspState = false;
    pdProcess->dspSwitch(_dspState);
};

// ---
void PdConsoleViewController::_menuPreferences()
{
    _displayPreferences = true;
}
void PdConsoleViewController::_menuAudioSettings()
{
    _displayAudioSettings = true;
}
