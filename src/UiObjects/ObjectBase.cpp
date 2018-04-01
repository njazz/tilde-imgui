
//
//  NodeObject.cpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#include "ObjectBase.hpp"

#include "IUWindowController.hpp"
#include "PdPatchViewController.hpp"

//int nameChanged(ImGuiTextEditCallbackData* o)
//{
//    NodeObject* obj = (NodeObject*)o->UserData;

//    obj->updated(NodeObject::oAutocomplete);

//    return 0;
//}

int ObjectBase::inletType(int idx)
{
    if (!pdObject)
        return 0;
    return (pdObject->inlets()[idx].type() != xpd::XLET_MESSAGE);
}

int ObjectBase::outletType(int idx)
{
    if (!pdObject)
        return 0;
    return (pdObject->outlets()[idx].type() != xpd::XLET_MESSAGE);
}

ImVec2 ObjectBase::inletPos(int idx)
{
    float d = (width / (inletCount - 1.0)) * idx - 12.0 * (idx > 0);
    if (inletCount <= 1)
        d = 0;
    return ImVec2(x, y) + ImVec2(0 + d, 0) + ImVec2(6, 0);
}

ImVec2 ObjectBase::outletPos(int idx)
{
    float d = (width / (outletCount - 1.0)) * idx - 12.0 * (idx > 0);
    if (outletCount <= 1)
        d = 0;
    return ImVec2(x, y) + ImVec2(0 + d, height - 4) + ImVec2(6, 0);
}

#pragma mark -

void ObjectBase::_drawInlet(int idx)
{
    //    const int NODE_SLOT_RADIUS = 5;
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 pos = inletPos(idx);

    ImU32 inletColor = IM_COL32(128, 128, 128, 0);
    if (inletType(idx))
        inletColor = IM_COL32(96, 128, 160, 255);

    ImGui::SetCursorScreenPos(pos - ImVec2(6, 3));
    ImGui::InvisibleButton("##btn", ImVec2(12, 10));

    if (ImGui::IsItemClicked()) {
        inletClicked = idx;
        updated(oInletClicked);
    }

    ImU32 inletBorderColor = IM_COL32(192, 192, 192, 255);
    if (ImGui::IsItemHovered())
        inletBorderColor = IM_COL32(0, 192, 255, 255);

    draw_list->AddRectFilled(pos - ImVec2(6, 0), pos - ImVec2(6, 0) + ImVec2(12, 4), inletColor);
    draw_list->AddRect(pos - ImVec2(6, 0), pos - ImVec2(6, 0) + ImVec2(12, 4), inletBorderColor);
}

void ObjectBase::_drawOutlet(int idx)
{
    //    const int NODE_SLOT_RADIUS = 5;
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 pos = outletPos(idx);

    ImGui::SetCursorScreenPos(pos - ImVec2(6, 3));
    ImGui::InvisibleButton("", ImVec2(12, 10));

    if (ImGui::IsItemClicked()) {
        outletClicked = idx;
        updated(oOutletClicked);
    }

    ImU32 outletColor = IM_COL32(128, 128, 128, 0);
    if (outletType(idx))
        outletColor = IM_COL32(96, 128, 160, 255);

    ImU32 outletBorderColor = IM_COL32(192, 192, 192, 255);
    if (ImGui::IsItemHovered())
        outletBorderColor = IM_COL32(0, 192, 255, 255);

    draw_list->AddRectFilled(pos - ImVec2(6, 0), pos - ImVec2(6, 0) + ImVec2(12, 4), outletColor);
    draw_list->AddRect(pos - ImVec2(6, 0), pos - ImVec2(6, 0) + ImVec2(12, 4), outletBorderColor);
}

void ObjectBase::_drawBackground()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    draw_list->ChannelsSetCurrent(1);

    ImU32 borderColor = (this->selected) ? IM_COL32(0, 192, 255, 255) : IM_COL32(192, 192, 192, 255);

    if (errorBox)
        borderColor = IM_COL32(255, 0, 0, 255);
    if (emptyBox)
        borderColor = IM_COL32(0, 192, 255, 255);

    ImVec2 node_rect_min = ImVec2(this->x, this->y);
    ImVec2 node_rect_max = node_rect_min + ImVec2(width, height); //ImGui::GetItemRectMax();

    draw_list->ChannelsSetCurrent(0); // Background
    draw_list->AddRectFilled(node_rect_min, node_rect_max, IM_COL32(75, 75, 75, 255), 4.0f);
    draw_list->AddRect(node_rect_min, node_rect_max, borderColor, 0.0f);
}

#pragma mark -

void ObjectBase::draw()
{
    if (hidden)
        return;

    ImGui::PushID(ImGui::GetID(id().c_str()));
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    //background
    draw_list->ChannelsSplit(2);

    _drawBackground();

    // inlets
    for (int slot_idx = 0; slot_idx < inletCount; slot_idx++) {
        _drawInlet(slot_idx);
    }

    // outlets
    for (int slot_idx = 0; slot_idx < outletCount; slot_idx++) {
        _drawOutlet(slot_idx);
    }

    drawObjectContents();

    draw_list->ChannelsMerge();

    ImGui::PopID();
}
