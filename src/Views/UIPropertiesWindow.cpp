
//
//  NodeObject.cpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#include "UIPropertiesWindow.hpp"

#include "imgui.h"

UIPropertiesWindow::UIPropertiesWindow(PropertyList* p, bool* d)
{
    _properties = p;
    _display = d;
}

void UIPropertiesWindow::_drawContents()
{
    if (!*_display)
        return;
    // properties window
    ImGui::PushID(ImGui::GetID((idString + "properties").c_str()));
    ImGui::Begin("Properties", _display, ImGuiWindowFlags_NoCollapse);
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 100);
    ImGui::SetColumnWidth(1, 200);

    for (auto n : _properties->names()) {

        ImGui::Text("%s", n.c_str());
        ImGui::NextColumn();

        ImGui::PushItemWidth(200);
        auto p = _properties->get(n);

        ImGui::PushID(ImGui::GetID((idString + "p" + n).c_str()));

        if (p) {
            if (p->type == ptString)
                ImGui::Text(": %s", _properties->get(n)->as<std::string>().c_str());

            if (p->type == ptBool) {
                bool v = _properties->get(n)->as<bool>();
                if (ImGui::Checkbox("", &v))
                    _properties->set(n, v);
            }
            if (p->type == ptVec2) {
                ImVec2 v = _properties->get(n)->as<ImVec2>();
                if(ImGui::DragFloat2("", (float*)&v))
                    _properties->set(n, v);
            }
            if (p->type == ptFloat) {
                float f = _properties->get(n)->as<float>();

                f = _properties->get(n)->as<float>();

                if (ImGui::DragFloat("", &f))
                {
                    _properties->set(n, f);
                }
            }

        } else
            ImGui::Text("ERR");
        ImGui::PopID();

        ImGui::NextColumn();
    }
    ImGui::End();
    ImGui::PopID();
};
