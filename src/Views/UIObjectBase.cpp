
//
//  NodeObject.cpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#include "UIObjectBase.hpp"

#include "IUWindowController.hpp"
#include "PdPatchViewController.hpp"

#include "Properties/PropertyList.h"

//int nameChanged(ImGuiTextEditCallbackData* o)
//{
//    NodeObject* obj = (NodeObject*)o->UserData;

//    obj->updated(NodeObject::oAutocomplete);

//    return 0;
//}

UiObjectBase::UiObjectBase()
{
    observer.callback = [this]() {

        std::string d;
        if (observer.data().size())
            d = observer.data().getStringAt(0);

        for (int i = 1; i < observer.data().size(); i++)
            d += " + " + observer.data().getStringAt(i);

        printf("callback: %s\n", d.c_str());

    };

    _createProperties();
}

int UiObjectBase::inletType(int idx)
{
    if (!pdObject)
        return 0;
    return (pdObject->inlets()[idx].type() != xpd::XLET_MESSAGE);
}

int UiObjectBase::outletType(int idx)
{
    if (!pdObject)
        return 0;
    return (pdObject->outlets()[idx].type() != xpd::XLET_MESSAGE);
}

ImVec2 UiObjectBase::inletPos(int idx)
{
    float d = ((width - 12) / (inletCount - 1.0)) * idx;
    if (inletCount <= 1)
        d = 0;
    return ImVec2(x, y) + ImVec2(0 + d, 0) + ImVec2(6, 0);
}

ImVec2 UiObjectBase::outletPos(int idx)
{
    float d = ((width - 12) / (outletCount - 1.0)) * idx;
    if (outletCount <= 1)
        d = 0;
    return ImVec2(x, y) + ImVec2(0 + d, height - 4) + ImVec2(6, 0);
}

#pragma mark -

void UiObjectBase::_drawInlet(int idx)
{
    //    const int NODE_SLOT_RADIUS = 5;
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 pos = inletPos(idx);

    ImU32 inletColor = IM_COL32(128, 128, 128, 0);
    if (inletType(idx))
        inletColor = IM_COL32(96, 128, 160, 255);

    ImGui::SetCursorScreenPos(pos - ImVec2(6, 3));
    ImGui::InvisibleButton("##btn", ImVec2(12, 10));

    if (editModePtr)
        if (*editModePtr)
            if (ImGui::IsItemClicked()) {
                data.inletClicked = idx;
                updated(oInletClicked);
            }

    ImU32 inletBorderColor = IM_COL32(192, 192, 192, 255);
    if (ImGui::IsItemHovered())
        inletBorderColor = IM_COL32(0, 192, 255, 255);

    draw_list->AddRectFilled(pos - ImVec2(6, 0), pos - ImVec2(6, 0) + ImVec2(12, 4), inletColor);
    draw_list->AddRect(pos - ImVec2(6, 0), pos - ImVec2(6, 0) + ImVec2(12, 4), inletBorderColor);
}

void UiObjectBase::_drawOutlet(int idx)
{
    //    const int NODE_SLOT_RADIUS = 5;
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 pos = outletPos(idx);

    ImGui::SetCursorScreenPos(pos - ImVec2(6, 3));
    ImGui::InvisibleButton("", ImVec2(12, 10));

    if (editModePtr)
        if (*editModePtr)
            if (ImGui::IsItemClicked()) {
                data.outletClicked = idx;
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

void UiObjectBase::_drawBackground()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    draw_list->ChannelsSetCurrent(1);

    ImU32 borderColor = (this->data.selected) ? IM_COL32(0, 192, 255, 255) : IM_COL32(192, 192, 192, 255);

    if (data.errorBox)
        borderColor = IM_COL32(255, 0, 0, 255);
    if (data.emptyBox)
        borderColor = IM_COL32(0, 192, 255, 255);

    ImVec2 node_rect_min = ImVec2(this->x, this->y);
    ImVec2 node_rect_max = node_rect_min + ImVec2(width, height); //ImGui::GetItemRectMax();

    draw_list->ChannelsSetCurrent(0); // Background
    draw_list->AddRectFilled(node_rect_min, node_rect_max, IM_COL32(75, 75, 75, 255), 4.0f);
    draw_list->AddRect(node_rect_min, node_rect_max, borderColor, 0.0f);
}

#pragma mark -

void UiObjectBase::draw()
{
    if (hidden)
        return;

    ImGui::PushID(ImGui::GetID(id().c_str()));
    ImGui::BeginGroup();

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    //background
    draw_list->ChannelsSplit(2);

    //updateOffset();

    _drawBackground();

    // inlets
    for (int slot_idx = 0; slot_idx < inletCount; slot_idx++) {
        _drawInlet(slot_idx);
    }

    // outlets
    for (int slot_idx = 0; slot_idx < outletCount; slot_idx++) {
        _drawOutlet(slot_idx);
    }

    // mouse handling
    if (editModePtr)
        if (!*editModePtr) {

            if (ImGui::IsMouseClicked(0) && ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height))) {
                onMouseDown(ImGui::GetIO().MousePos);
            }

            if (ImGui::IsMouseClicked(1) && ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height))) {
                onMouseRightClick(ImGui::GetIO().MousePos);
            }

            if (ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height))) {
                onMouseHover(ImGui::GetIO().MousePos);
            }

            if (ImGui::IsMouseReleased(0) && ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height))) {
                onMouseUp(ImGui::GetIO().MousePos);
            }

            if (ImGui::IsMouseDragging(0)) { // && ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height))) {
                onMouseDrag(ImGui::GetIO().MouseDelta);
            }

            if (ImGui::IsMouseDoubleClicked(0) && ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height))) {
                onMouseDoubleClick(ImGui::GetIO().MousePos);
            }
        }

    drawObjectContents();

    draw_list->ChannelsMerge();

    //
    // properties window
    /*
    ImGui::BeginTooltip();
    ImGui::Text("properties:");
    ImGui::Separator();
    for (auto n : properties.names())
    {
        ImGui::Text("%s",n.c_str());
        ImGui::SameLine();
        ImGui::Text(": %s", properties.get(n)->as<std::string>().c_str());
    }
    ImGui::EndTooltip();
    */

    ImGui::EndGroup();
    ImGui::PopID();
}

//
void UiObjectBase::updateFromPdObject()
{
    data.errorBox = (pdObject == 0);

    if (pdObject) {
        inletCount = pdObject->inletCount();
        outletCount = pdObject->outletCount();
        std::string info = objectText + " ins: " + std::to_string(inletCount) + " outs:" + std::to_string(outletCount);
    }
}

void UiObjectBase::pdObjUpdatePosition()
{
    if (!pdObject)
        return;
    pdObject->setX(x);
    pdObject->setY(y);
}

std::string UiObjectBase::asPdFileString()
{
    return "#X obj " + std::to_string(int(x)) + " " + std::to_string(int(y)) + " " + objectText;
}