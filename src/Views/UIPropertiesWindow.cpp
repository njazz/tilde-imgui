
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

    idString = "PW"+std::to_string((long)this);
}

void UIPropertiesWindow::_drawContents()
{
    if (!*_display)
        return;
    // properties window
    ImGui::PushID(ImGui::GetID((idString + "properties").c_str()));

    // todo
    ImGui::SetNextWindowSize(ImVec2(320,320));
    ImGui::SetNextWindowPos(ImVec2(x,y),ImGuiCond_Once);
    ImGui::Begin(std::string("Properties ("+std::to_string((long)this)+")").c_str(), _display, ImGuiWindowFlags_NoCollapse);
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
            if (p->typed<std::string>()) { //p->type == ptString)
                ImGui::Text(": %s", _properties->get(n)->typed<std::string>()->get().c_str());
            }

            if (p->typed<bool>()) { //type == ptBool) {
                bool v = _properties->get(n)->typed<bool>()->get();
                if (ImGui::Checkbox("", &v))
                    _properties->set(n, v);
            }
            if (p->typed<bool*>()) { //type == ptBool) {
                bool* v_p = _properties->get(n)->typed<bool*>()->get();
                if (ImGui::Checkbox("", v_p))
                    _properties->set(n, v_p);
            }
            if (p->typed<std::vector<float*> >()) { //>type == ptVec2) {
                auto vec = _properties->get(n)->typed<std::vector<float*> >()->get();
                if (vec.size()<2) return;
                ImVec2 v = ImVec2(*vec[0], *vec[1]);
                if (ImGui::DragFloat2("", (float*)&v)) {
                    *vec[0] = v.x;
                    *vec[1] = v.y;
                    _properties->set(n, vec);
                }
            }
            if (p->typed<float>()) { //type == ptFloat) {
                float f = _properties->get(n)->typed<float>()->get();

                //f = _properties->get(n)->as<float>();

                if (ImGui::DragFloat("", &f)) {
                    _properties->set(n, f);
                }
            }
            if (p->typed<float*>()) { //type == ptFloat) {
                float* f_p = _properties->get(n)->typed<float*>()->get();

                //f = _properties->get(n)->as<float>();

                if (ImGui::DragFloat("", f_p)) {


                    _properties->set(n, f_p);
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
