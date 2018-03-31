//
//  NodeInlet.cpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#include "NewConnection.hpp"
#include "UiObjects/NodeObject.hpp"

void NewConnection::draw()
{
    if (!outputObj)
        return;

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 offset = ImVec2(0, 0);

    ImVec2 p1 = offset + outputObj->outletPos(outputIdx);
    ImVec2 p2;

    if (inputObj!=0)
         p2 = offset + inputObj->inletPos(inputIdx);
    else
         p2 = offset + ImVec2(inputX, inputY);

    draw_list->AddBezierCurve(p1, p1 + ImVec2(0, 30), p2 + ImVec2(0, -30), p2, IM_COL32(0, 192, 255, 255), 1.0f);
}
