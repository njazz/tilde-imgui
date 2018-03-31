
//
//  AppController.cpp
//  imguiController
//
//  Created by Alex on 22/03/2018.
//

#include "AppController.hpp"

void PdConsoleViewController::_drawMenu()
{
    _menu.draw();

//    return;
//    //
//    ImGui::BeginMainMenuBar();
//    if (ImGui::BeginMenu("File")) {

//        if (ImGui::MenuItem("New patch window", "Cmd + N")) {
//            updated(oMenuNew);
//            windowController()->restoreContext();
//        }

//        ImGui::MenuItem("Open in new window...", "Cmd + O");

//        ImGui::Separator();
//        if (ImGui::MenuItem("Exit", "Cmd + Q")) {
//            updated(oMenuExit);
//            windowController()->restoreContext();
//        }
//        ImGui::EndMenu();
//    }

//    if (ImGui::BeginMenu("Window")) {
//        ImGui::MenuItem("Settings ...");
//        ImGui::MenuItem("Audio / MIDI setup...");
//        ImGui::Separator();
//        ImGui::MenuItem("Clear console");
//        ImGui::EndMenu();

//    }

//    if (ImGui::BeginMenu("Media")) {
//        ImGui::MenuItem("DSP On");
//        ImGui::MenuItem("DSP Off");
//        ImGui::EndMenu();
//    }
//    ImGui::EndMainMenuBar();
}

void PdConsoleViewController::draw()
{
//    windowController()->restoreContext();

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
