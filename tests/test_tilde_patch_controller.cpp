#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PdPatchViewController.hpp"

#include "mocks/mock_imgui_mvc.h"
#include "mocks/mock_canvas_data.h"
#include "mocks/mock_patch_menus.h"
#include "mocks/mock_uiobject_base.h"
#include "mocks/mock_uiobject.h"
#include "mocks/mock_preferences.h"
#include "mocks/mock_app_controller.h"
#include "mocks/mock_common_menus.h"
#include "mocks/mock_grid.h"
#include "mocks/mock_view_controllers.h"
#include "mocks/mock_undostack.h"
#include "mocks/mock_object_menu.h"
#include "mocks/mock_filesaver.h"
#include "mocks/mock_arrangeobjects.h"
#include "mocks/mock_properties_window.h"

TEST_CASE("patch controller: basic", "[tilde~ PureData IDE]")
{
    SECTION("1")
    {
        // TODO
        PdPatchViewController pvc(0);
    }
};
