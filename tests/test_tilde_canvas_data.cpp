#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CanvasData.h"

#include "mocks/mock_imgui_mvc.h"
#include "mocks/mock_canvas_data.h"
#include "mocks/mock_views.h"

TEST_CASE("canvas_data: basic", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        CanvasData cd;

        REQUIRE(cd.hasObjectsOrPatchcords() == 0);
        REQUIRE(cd.hasSelectedObjectsOrPatchcords() == 0);

        TestObject obj1;
        TestObject obj2;
        TestObject obj3;

        TestObject obj_outside;

        cd.addObject(&obj1);
        cd.addObject(&obj2);
        cd.addObject(&obj3);

        REQUIRE(cd.hasObjectsOrPatchcords() == 1);
        REQUIRE(cd.hasSelectedObjectsOrPatchcords() == 0);

        // one
        cd.selectObject(&obj1);
        REQUIRE(cd.hasSelectedObjectsOrPatchcords() == 1);
        cd.deselectObjects();
        REQUIRE(cd.hasSelectedObjectsOrPatchcords() == 0);

        // select all
        cd.selectAllObjects();
        REQUIRE(cd.hasObjectsOrPatchcords() == 1);
        REQUIRE(cd.hasSelectedObjectsOrPatchcords() == 1);
        cd.deselectObjects();
        REQUIRE(cd.hasSelectedObjectsOrPatchcords() == 0);

        // index
        REQUIRE(cd.findObjectIndex(&obj1)==0);
        REQUIRE(cd.findObjectIndex(&obj2)==1);
        REQUIRE(cd.findObjectIndex(&obj3)==2);

        cd.deleteObject(&obj2);
        cd.addObject(&obj2);

        REQUIRE(cd.findObjectIndex(&obj1)==0);
        REQUIRE(cd.findObjectIndex(&obj3)==1);
        REQUIRE(cd.findObjectIndex(&obj2)==2);

        REQUIRE(cd.getObjectByIndex(0) == &obj1);
        REQUIRE(cd.getObjectByIndex(1) == &obj3);
        REQUIRE(cd.getObjectByIndex(2) == &obj2);

    }
    SECTION("patchcords")
    {
        CanvasData cd;

        UIPatchcord p1;
        UIPatchcord p2;

        cd.addPatchcord(&p1);
        cd.addPatchcord(&p2);

        REQUIRE(cd.hasObjectsOrPatchcords() == 1);
        REQUIRE(cd.hasSelectedObjectsOrPatchcords() == 0);
        cd.selectAllPatchcords();
        REQUIRE(cd.hasSelectedObjectsOrPatchcords() == 1);

        cd.deleteSelectedPatchcords();
        REQUIRE(cd.hasObjectsOrPatchcords() == 0);
        REQUIRE(cd.hasSelectedObjectsOrPatchcords() == 0);
    }
}
