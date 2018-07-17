#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "FileParser.h"

#include "mocks/mock_imgui_mvc.h"
#include "mocks/mock_views.h"
#include "mocks/mock_view_controllers.h"
#include "mocks/mock_canvas_data.h"

#include "FileSaver.h"

TEST_CASE("view controller stack: basic", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        PdPatchViewControllerStack stack;

        PdCommonMenus m;

        PdPatchViewController pvc1(&m);
        PdPatchViewController pvc2(&m);


        REQUIRE(stack.size() == 0);
        stack.push(&pvc1);
        REQUIRE(stack.size() == 1);
        REQUIRE(stack.last() == &pvc1);
        stack.push(&pvc2);
        REQUIRE(stack.size() == 2);
        REQUIRE(stack.last() == &pvc2);
        stack.pop();
        REQUIRE(stack.size() == 1);
        REQUIRE(stack.last() == &pvc1);
        stack.pop();
        REQUIRE(stack.size() == 0);

    }
}


TEST_CASE("file parser", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
       // TODO

    }
}

TEST_CASE("file saver", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        // TODO
    }
}
