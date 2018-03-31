#include "catch.hpp"

#include "abstractserverprocess.h"
#include "canvas.h"
#include "pd_canvas.h"
#include "pd_floatarray.h"
#include "pd_localserver.h"
#include "pd_object.h"

#include <algorithm>
#include <memory>
#include <numeric>
#include <string>

using namespace xpd;

TEST_CASE("PdFloatArray", "[PdFloatArray]")
{
    PdLocalServer srv(ServerSettings("local"));
    ProcessPtr p = srv.createProcess();
    CanvasPtr c = p->createCanvas();

    SECTION("init")
    {
        PdFloatArray arr(c.get(), "array1", 10);
        REQUIRE(arr.size() == 10);
        REQUIRE_FALSE(arr.empty());
        REQUIRE(arr.name() == "array1");
        REQUIRE(arr.plotStyle() == FloatArray::PLOT_LINES);
        REQUIRE(arr.id() != 0);
        REQUIRE(arr.type() == OBJ_TYPE_ARRAY);

        REQUIRE(arr.at(0) == 0.f);
        REQUIRE(arr.at(9) == 0.f);
        REQUIRE_THROWS_AS(arr.at(10), FloatArray::Exception);

        REQUIRE_THROWS_AS(PdFloatArray(nullptr, "array2", 1000), FloatArray::Exception);
    }

    SECTION("id")
    {
        PdFloatArray a0(c.get(), "array1", 10);
        PdFloatArray a1(c.get(), "array2", 10);

        REQUIRE(a0.id() != a1.id());
        REQUIRE(a0.id() < a1.id());
    }

    SECTION("resize")
    {
        PdFloatArray arr(c.get(), "array1", 10);

        REQUIRE(arr.resize(5));
        REQUIRE_FALSE(arr.resize(0));
    }

    SECTION("plotStyle")
    {
        PdFloatArray arr(c.get(), "array1", 10);

        REQUIRE(arr.plotStyle() == FloatArray::PLOT_LINES);
        arr.setPlotStyle(FloatArray::PLOT_POINTS);
        REQUIRE(arr.plotStyle() == FloatArray::PLOT_POINTS);
        arr.setPlotStyle(FloatArray::PLOT_BEZIER);
        REQUIRE(arr.plotStyle() == FloatArray::PLOT_BEZIER);
    }

    SECTION("fill")
    {
        PdFloatArray arr(c.get(), "array1", 10);

        arr.fill(1000);
        REQUIRE(arr.at(0) == 1000.f);
        REQUIRE(arr.at(1) == 1000.f);
        REQUIRE(arr.at(9) == 1000.f);

        REQUIRE(arr.resize(5));
        arr.fill(2000);
        REQUIRE(arr.at(0) == 2000.f);
        REQUIRE(arr.at(4) == 2000.f);
    }

    SECTION("container")
    {
        PdFloatArray arr(c.get(), "array1", 4);
        arr.front() = 100;
        arr.back() = 200;

        REQUIRE(arr.front() == 100.f);
        REQUIRE(arr.back() == 200.f);

        *arr.begin() = 1000;
        REQUIRE(arr.front() == 1000.f);
        REQUIRE(arr.begin()[0] == 1000.f);
    }

    SECTION("iterators")
    {
        PdFloatArray arr(c.get(), "array1", 10);

        REQUIRE(arr.front() == 0.f);
        REQUIRE(arr.back() == 0.f);

        REQUIRE(arr.begin() != arr.end());
        REQUIRE_FALSE(arr.begin() == arr.end());

        for (auto it = arr.begin(); it != arr.end(); ++it) {
            REQUIRE(*it == 0.f);
        }

        for (auto it = arr.begin(); it != arr.end(); it++) {
            REQUIRE(*it == 0.f);
        }

        for (auto it = arr.rend(); it != arr.rbegin(); ++it) {
            REQUIRE(*it == 0.f);
        }

        for (auto it = arr.rend(); it != arr.rbegin(); it++) {
            REQUIRE(*it == 0.f);
        }

        REQUIRE(std::min_element(arr.begin(), arr.end()) == arr.begin());
        REQUIRE(std::max_element(arr.begin(), arr.end()) == arr.begin());
        std::fill(arr.begin(), arr.end(), -100.f);

        REQUIRE(arr.front() == -100.f);
        REQUIRE(arr.back() == -100.f);

        std::iota(arr.begin(), arr.end(), 1);
        REQUIRE(arr.front() == 1.f);
        REQUIRE(arr.back() == 10.f);

        std::transform(std::begin(arr), std::end(arr), std::begin(arr), [](float f) { return f * f; });
        REQUIRE(arr.begin()[0] == 1.f);
        REQUIRE(arr.begin()[1] == 4.f);
        REQUIRE(arr.begin()[2] == 9.f);
        REQUIRE(arr.begin()[3] == 16.f);

        std::iota(arr.rend(), arr.rbegin(), 1);
        REQUIRE(arr.front() == 10.f);
        REQUIRE(arr.back() == 1.f);

        REQUIRE(std::min_element(arr.begin(), arr.end()) == arr.end() - 1);
        REQUIRE(std::max_element(arr.begin(), arr.end()) == arr.begin());

        REQUIRE(std::find(arr.begin(), arr.end(), 3) == std::begin(arr) + 7);
    }
}
