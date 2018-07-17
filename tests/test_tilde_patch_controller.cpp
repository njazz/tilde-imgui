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

bool operator==(ImVec2 a, ImVec2 b){return  (a.x == b.x) && (a.y == b.y);}

TEST_CASE("patch controller: basic", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        // TODO
        PdPatchViewController pvc(0);

        // false without pd process
        REQUIRE(!pvc.createObject("test",0,0));

        // todo: integration / mock


    }

    // TODO: integration test with CanvasData
//    SECTION("drag")
//    {
//        PdPatchViewController pvc(0);

//        pvc.createObject("+",0,0);
//        pvc.createObject("+",10,10);

//        pvc.data.selectAllObjects();

//        pvc.dragSelectedObjects(ImVec2(10,10));

//        REQUIRE(pvc.data.objects[0]->pos() == ImVec2(10,10));
//        REQUIRE(pvc.data.objects[1]->pos() == ImVec2(20,20));
//    }
};
