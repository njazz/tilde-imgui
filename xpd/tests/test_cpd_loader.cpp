#include "catch.hpp"

#include "cpd/cpd.h"
#include "cpd/cpd_catcher.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_loader", "[cpd PureData wrapper]")
{
    SECTION("load_library")
    {
        REQUIRE(cpd_load_library(cpd_symbol("not-exists")) == 0);
    }

    SECTION("loadbang")
    {
        cpd_canvas_loadbang(NULL);
        cpd_catcher_init();

        auto cnv = cpd_patch_new();
        REQUIRE(cnv);

        auto obj = cpd_object_new(cnv, "loadbang", 0, 0, 0);
        REQUIRE(obj);
        auto catcher = cpd_catcher_new(cnv);
        REQUIRE(catcher);
        REQUIRE(cpd_connect(obj, 0, catcher, 0));

        // NULL loadbang
        cpd_canvas_loadbang(NULL);
        REQUIRE(!cpd_catcher_last_bang(catcher));

        // canvas loadbang
        cpd_canvas_loadbang(cnv);
        REQUIRE(cpd_catcher_last_bang(catcher));

        REQUIRE(cpd_canvas_free(cnv));
    }
}
