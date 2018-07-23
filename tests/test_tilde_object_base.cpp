#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "imgui.h"
#include "mocks/mock_imgui_mvc.h"
#include "mocks/mock_views.h"

#include "UIObjectBase.hpp"

void UIObjectData::syncFromServerObject(){};

//

void ImDrawList::ChannelsMerge(){};
void ImDrawList::ChannelsSplit(int channels_count){};
void ImDrawList::ChannelsSetCurrent(int channel_index){};
void ImDrawList::AddRect(const ImVec2& a, const ImVec2& b, ImU32 col, float rounding, int rounding_corners_flags, float thickness){};

bool ImGui::Begin(const char* name, bool* p_open, ImGuiWindowFlags flags) { return true; };
bool ImGui::BeginChild(const char* str_id, const ImVec2& size, bool border, ImGuiWindowFlags flags) { return true; };
bool ImGui::BeginChild(ImGuiID id, const ImVec2& size, bool border, ImGuiWindowFlags flags) { return true; };
bool ImGui::BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags) { return true; };
void ImGui::End(){};
void ImGui::EndChild(){};
void ImGui::EndCombo(){};
void ImGui::PushItemWidth(float item_width){};

void ImGui::SetNextWindowPos(const ImVec2& pos, ImGuiCond cond, const ImVec2& pivot){};
void ImGui::SetNextWindowSize(const ImVec2& size, ImGuiCond cond){};
void ImGui::SetNextWindowBgAlpha(float alpha){};

void ImGui::Separator(){};
void ImGui::SameLine(float pos_x, float spacing_w){};

void ImGui::Text(const char* fmt, ...){};
bool ImGui::Button(const char* label, const ImVec2& size) { return false; };
bool ImGui::Checkbox(const char* label, bool* v) { return false; };
bool ImGui::InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data) { return false; };

void ImGui::ShowMetricsWindow(bool* p_open){};

// stub

void ImGui::BeginGroup(){};

bool ImGui::IsItemClicked(int mouse_button) { return true; }
bool ImGui::IsItemHovered(ImGuiHoveredFlags flags) { return true; }
bool ImGui::IsMouseDragging(int button, float lock_threshold) { return true; }
bool ImGui::IsMouseDoubleClicked(int button) { return true; }

bool ImGui::InvisibleButton(const char* str_id, const ImVec2& size) { return false; }

void ImGui::SetCursorScreenPos(const ImVec2& screen_pos){};

bool ImGui::IsMouseHoveringRect(const ImVec2& r_min, const ImVec2& r_max, bool clip) { return true; };

void ImGui::PopID(){};
void ImGui::PushID(int int_id){};

void ImGui::EndGroup(){};

bool ImGui::IsKeyDown(int user_key_index) { return false; }

void ImGui::OpenPopup(const char* str_id){};

TEST_CASE("object_base: basic", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        ///\todo stub
        UiObjectBase bb;

        REQUIRE(true);

        // crash-proof without pdObject:
        bb.draw();
        bb.pdObjUpdatePosition();
        REQUIRE(true);

    }

}
