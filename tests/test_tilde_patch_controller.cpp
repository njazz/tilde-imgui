#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PdPatchViewController.hpp"

#include "mocks/mock_imgui_mvc.h"
#include "mocks/mock_canvas_data.h"
#include "mocks/mock_patch_menus.h"
#include "mocks/mock_uiobject.h"
#include "mocks/mock_app_controller.h"

TEST_CASE("patch controller: basic", "[tilde~ PureData IDE]")
{
    SECTION("1")
    {
        // TODO
        PdPatchViewController pvc(0);
    }
};
