#include "catch.hpp"

#include "array.h"

#include <memory>
#include <string>

using namespace xpd;

TEST_CASE("Array", "[Array]")
{
    SECTION("init")
    {
        FloatArray arr(nullptr, "array1", 10);
        REQUIRE(arr.size() == 10);
        REQUIRE(arr.name() == "array1");
        REQUIRE(!arr.empty());

        REQUIRE(arr.resize(10));
        REQUIRE_FALSE(arr.resize(20));
        REQUIRE(arr.plotStyle() == FloatArray::PLOT_LINES);
        arr.setPlotStyle(FloatArray::PLOT_POINTS);
        REQUIRE(arr.plotStyle() == FloatArray::PLOT_POINTS);
        REQUIRE_THROWS_AS(arr.at(0), FloatArray::Exception);
        REQUIRE_THROWS_AS(arr.fill(0), FloatArray::Exception);

        REQUIRE(arr.type() == OBJ_TYPE_ARRAY);
    }
}
