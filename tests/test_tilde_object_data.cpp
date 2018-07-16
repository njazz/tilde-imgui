#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "mocks/mock_imgui_mvc.h"
#include "mocks/mock_views.h"

#include "UIObjectData.h"

TEST_CASE("object_data: basic", "[tilde~ PureData IDE]")
{
    SECTION("1")
    {
        UIObjectData od;

        od.properties()->create("Existing","Test","0.1",0.33f);

        od.setData("obj @Existing 1");

        REQUIRE(od.properties()->get("Existing")->typed<float>()->get()==1);

    }
}
