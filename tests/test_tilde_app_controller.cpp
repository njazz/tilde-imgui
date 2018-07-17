#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "AppController.hpp"

#include "mocks/mock_imgui_mvc.h"
#include "mocks/mock_patch_controller.h"
#include "mocks/mock_clipboard.h"
#include "mocks/mock_patch_menus.h"
#include "mocks/mock_preferences.h"
#include "mocks/mock_uiobject_base.h"
#include "mocks/mock_uiobject.h"
#include "mocks/mock_patch_controller.h"
#include "mocks/mock_fileparser.h"
#include "mocks/mock_grid.h"
#include "mocks/mock_undostack.h"
#include "mocks/mock_canvas_data.h"
#include "mocks/mock_properties_window.h"
#include "mocks/mock_object_menu.h"
#include "mocks/mock_common_menus.h"
#include "mocks/mock_view_controllers.h"
#include "mocks/mock_console_controller.h"
#include "mocks/mock_app_controller_base.h"
#include "mocks/mock_preferences.h"

void setupUIObjectsLibrary(){}

TEST_CASE("appcontroller: basic", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        AppController ac;
    }
}
