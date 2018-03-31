#include "catch.hpp"

#include "cpd/cpd.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_environment", "[cpd PureData wrapper]")
{
    SECTION("version")
    {
        REQUIRE(cpd_version_major() == 0);
        REQUIRE(cpd_version_minor() >= 47);
        REQUIRE(cpd_version_bugfix() >= 0);
    }

    SECTION("seachpath")
    {
        REQUIRE(cpd_searchpath_num() == 0);
        cpd_searchpath_append("~");
        REQUIRE(cpd_searchpath_num() == 1);
        cpd_searchpath_append("/Library/Pd");
        REQUIRE(cpd_searchpath_num() == 2);

        // double insertion
        cpd_searchpath_append("/Library/Pd");
        REQUIRE(cpd_searchpath_num() == 2);

        REQUIRE(cpd_searchpath_at(0) == std::string("~"));
        REQUIRE(cpd_searchpath_at(1) == std::string("/Library/Pd"));
        REQUIRE(cpd_searchpath_at(2) == 0);

        cpd_searchpath_clear();
        REQUIRE(cpd_searchpath_num() == 0);
        cpd_searchpath_append("~");
        //        REQUIRE(cpd_searchpath_num() == 1);
    }
}
