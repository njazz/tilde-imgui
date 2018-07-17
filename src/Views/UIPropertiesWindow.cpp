
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

    idString = "PW" + std::to_string((long)this);
}

void UIPropertiesWindow::_drawContents()
{
    if (!_properties) return;
    if (!_display) return;

    if (!*_display)
        return;
    // properties window
    ImGui::PushID(ImGui::GetID((idString + "properties").c_str()));

    // todo
    ImGui::SetNextWindowSize(ImVec2(320, 320));
    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
    ImGui::Begin(std::string("Properties (" + std::to_string((long)this) + ")").c_str(), _display, ImGuiWindowFlags_NoCollapse);

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 100);
    ImGui::SetColumnWidth(1, 200);

    for (auto g : _properties->groupNames()) {
        auto grp = _properties->fromGroup(g);

        auto _id = std::string(std::to_string((long)this) + "_p" + g);
        ImGui::NextColumn();
        ImGui::Text("%s", g.c_str());
        ImGui::NextColumn();
        ImGui::Separator();

        //        ImGui::BeginChildFrame(ImGui::GetID(_id.c_str()), ImVec2(0, 0));

        for (auto n : _properties->namesInGroup(grp)) {

            ImGui::Text("%s", n.c_str());
            ImGui::NextColumn();

            ImGui::PushItemWidth(200);
            auto p = _properties->get(n);

            ImGui::PushID(ImGui::GetID((idString + "p" + n).c_str()));

            if (p) {
                if (p->typed<std::string>()) { //p->type == ptString)
                    if (p->readOnly)
                        ImGui::Text("%s", _properties->get(n)->typed<std::string>()->get().c_str());
                    else

                    {
                        // todo:
//                        auto str =_properties->get(n)->typed<std::string>()->get();
//                        ImGui::InputText("", str.c_str(), str.length());
                         ImGui::Text("edit: %s", _properties->get(n)->typed<std::string>()->get().c_str());
                    }
                }

                else if (p->typed<std::vector<std::string> >()) {
                    auto arr = _properties->get(n)->typed<std::vector<std::string> >()->get();

                    for (auto s:arr)
                    {
                        ImGui::Text("%s",s.c_str());
                    }
                    ImGui::Button("+");
                }

                else if (p->typed<bool>()) { //type == ptBool) {
                    bool v = _properties->get(n)->typed<bool>()->get();
                    if (ImGui::Checkbox("", &v))
                        _properties->set(n, v);
                }
                else if (p->typed<bool*>()) { //type == ptBool) {
                    bool* v_p = _properties->get(n)->typed<bool*>()->get();
                    if (ImGui::Checkbox("", v_p))
                        _properties->set(n, v_p);
                }
                else if (p->typed<std::vector<float*> >()) { //>type == ptVec2) {
                    auto vec = _properties->get(n)->typed<std::vector<float*> >()->get();
                    if (vec.size() < 2)
                        return;
                    ImVec2 v = ImVec2(*vec[0], *vec[1]);
                    if (ImGui::DragFloat2("", (float*)&v)) {
                        *vec[0] = v.x;
                        *vec[1] = v.y;
                        _properties->set(n, vec);
                    }
                }
                else if (p->typed<float>()) { //type == ptFloat) {
                    float f = _properties->get(n)->typed<float>()->get();

                    //f = _properties->get(n)->as<float>();

                    if (ImGui::DragFloat("", &f)) {
                        _properties->set(n, f);
                    }
                }
                else if (p->typed<float*>()) { //type == ptFloat) {
                    float* f_p = _properties->get(n)->typed<float*>()->get();

                    //f = _properties->get(n)->as<float>();

                    if (ImGui::DragFloat("", f_p)) {

                        _properties->set(n, f_p);
                    }
                }

                else
                                ImGui::Text("ERR");
            }

            ImGui::PopID();

            ImGui::NextColumn();
        }

        //        ImGui::EndChildFrame();
        ImGui::Separator();
    }
    ImGui::End();
    ImGui::PopID();
};
