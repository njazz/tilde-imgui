
//
//  AppController.cpp
//  imguiController
//
//  Created by Alex on 22/03/2018.
//

#include "AppController.hpp"

PdConsoleViewController::PdConsoleViewController(PdCommonMenus* m)
    : _menu(m)
{
    _menu.common->menuWindow.setAction(PdCommonWindowMenu::aClearConsole, &clearConsole);
    _menu.common->menuMedia.setAction(PdCommonMediaMenu::aDSPOn, &dspOn);
    _menu.common->menuMedia.setAction(PdCommonMediaMenu::aDSPOff, &dspOff);
    _menu.common->menuMedia.dspOn = &_dspOn;
}

void PdConsoleViewController::_drawMenu()
{
    _menu.setWindowController(windowController());
    _menu.common->setWindowController(windowController());
    _menu.draw();
}

void PdConsoleViewController::draw()
{

    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::SetNextWindowPos(ImVec2(0, 20));

    ImGui::Begin("pd_console");

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

    if (ImGui::Checkbox("DSP", &_dspOn)) {
        pdProcess->dspSwitch(_dspOn);
    }

    ImGui::Separator();
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
};

void PdConsoleViewController::post(std::string line)
{
    _consoleText = line + "\n" + _consoleText;
}

void PdConsoleViewController::setWindowController(IUWindowController* w)
{
    IULayer::setWindowController(w);
    _menu.setWindowController(w);
};
