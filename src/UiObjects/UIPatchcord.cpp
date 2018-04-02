//
//  NodeInlet.cpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#include "UiObjects/UIPatchcord.hpp"

#include "UiObjects/UIObject.hpp"

void UIPatchcord::draw()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 offset = ImVec2(0, 0);

    ImVec2 p1 = offset + outputObj->outletPos(outputIdx);
    ImVec2 p2 = offset + inputObj->inletPos(inputIdx);

    draw_list->AddBezierCurve(p1, p1 + ImVec2(0, 30), p2 + ImVec2(0, -30), p2, IM_COL32(200, 200, 100, 255), 1.0f);

    if (outputObj->outletType(outputIdx)) {
        draw_list->AddBezierCurve(p1, p1 + ImVec2(1, 30), p2 + ImVec2(1, -30), p2, IM_COL32(200, 200, 100, 255), 1.0f);
        draw_list->AddBezierCurve(p1, p1 + ImVec2(-1, 30), p2 + ImVec2(-1, -30), p2, IM_COL32(200, 200, 100, 255), 1.0f);
    }
}
