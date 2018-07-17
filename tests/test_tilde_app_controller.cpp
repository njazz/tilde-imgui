#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "AppController.hpp"

#include "mocks/mock_imgui_mvc.h"
#include "mocks/mock_patch_controller.h"
#include "mocks/mock_clipboard.h"
#include "mocks/mock_patch_menus.h"
#include "mocks/mock_preferences.h"
#include "mocks/mock_uiobject.h"
#include "mocks/mock_patch_controller.h"
#include "mocks/mock_fileparser.h"

TEST_CASE("appcontroller: basic", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        AppController ac;
    }
}
