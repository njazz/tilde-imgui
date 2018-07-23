#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PdConsoleViewController.hpp"

#include "mocks/mock_app_controller.h"
#include "mocks/mock_common_menus.h"
#include "mocks/mock_imgui_mvc.h"
#include "mocks/mock_preferences.h"
#include "mocks/mock_properties_window.h"

#include "imgui.h"

// --- imgui calls mock:

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
//

void IUAction::action()
{
    _callback();
}

TEST_CASE("console controller: basic", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        ///>\todo test with menu object
        PdConsoleViewController cv(0);
    }

    SECTION("dummy tests")
    {
        // stub. checks if doesn't fail without pdProcess

        PdConsoleViewController cv(0);

        cv.dspOn();
        cv.dspOff();

        cv.draw();
        cv.drawMenu();

        // didn't crash yet:
        REQUIRE(true);
    }
}
