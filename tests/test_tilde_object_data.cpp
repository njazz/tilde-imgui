#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "mocks/mock_imgui_mvc.h"
#include "mocks/mock_views.h"

#include "UIObjectData.h"

TEST_CASE("object_data: basic", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        UIObjectData od;

        od.properties()->create("Existing","Test","0.1",0.33f);

        std::string str = "obj @Existing 1";
        od.setData(str);

        REQUIRE(od.properties()->get("Existing")->typed<float>()->get()==1);
        REQUIRE(!strncmp(od.data().c_str(), str.c_str(), 3));
        REQUIRE(od.data().length() != str.length());

    }
}
