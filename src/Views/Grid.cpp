//
//  NodeInlet.cpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#include "Grid.hpp"
#include "UIObjects/UIObject.hpp"

//static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
//static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

Grid::Grid()
{
    manualLayout = true;
    mouseEnabled = false;
    flags = flags | ImGuiWindowFlags_HorizontalScrollbar;

    alpha = 0;
}

void Grid::_drawContents()
{

    if (!editModeFlag)
        return;
    if (!showGrid)
        return;
    if (!gridStep)
        return;

    //contentSize= ImVec2(800,600);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 scrolling;

    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::SetNextWindowBgAlpha(0);
    ImGui::BeginChild(ImGui::GetID("grid"));
    if (*editModeFlag && *showGrid) {
        ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
        float GRID_SZ = *gridStep; //30.0f;

        offset = ImGui::GetCursorScreenPos();
        ImVec2 win_pos = offset; // - ImVec2(0, 0);
        ImVec2 canvas_sz = ImVec2(contentSize.x, contentSize.y - 20); //ImGui::GetWindowSize();

        for (float x = fmodf(scrolling.x, GRID_SZ); x < contentSize.x; x += GRID_SZ)
            draw_list->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, contentSize.y - 20) + win_pos, GRID_COLOR);
        for (float y = fmodf(scrolling.y, GRID_SZ); y < contentSize.y - 20; y += GRID_SZ)
            draw_list->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(contentSize.x, y) + win_pos, GRID_COLOR);
    }
    ImGui::EndChild();
    ImGui::SetCursorPos(ImVec2(0, 0));
};
