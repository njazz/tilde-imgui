#include "catch.hpp"

#include "cpd/cpd.h"
#include "cpd/cpd_connection.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_connection", "[cpd PureData wrapper]")
{
    auto cnv = cpd_patch_new();

    SECTION("base")
    {
        auto obj1 = cpd_object_new(cnv, "f", 0, 0, 0);
        auto obj2 = cpd_object_new(cnv, "+", 0, 0, 0);
        auto obj3 = cpd_object_new(cnv, "sqrt", 0, 0, 0);
        auto obj4 = cpd_object_new(cnv, "moses", 0, 0, 0);

        REQUIRE(cpd_object_out_connections(obj1) == 0);
        REQUIRE(cpd_object_out_connections(obj2) == 0);
        REQUIRE(cpd_object_out_connections(obj3) == 0);
        REQUIRE(cpd_object_out_connections(obj4) == 0);

        // [+] -> [sqrt]
        REQUIRE(cpd_connect(obj2, 0, obj3, 0));
        auto conn0 = cpd_object_out_connections(obj2);
        REQUIRE(cpd_connection_count(conn0) == 1);
        REQUIRE(cpd_connection_next(conn0) == 0);
        REQUIRE(cpd_connection_type(conn0) == CPD_CONNECTION_CONTROL);
        REQUIRE(cpd_connection_source(conn0) == obj2);
        REQUIRE(cpd_connection_destination(conn0) == obj3);
        REQUIRE(cpd_connection_source_outlet(conn0) == 0);
        REQUIRE(cpd_connection_destination_inlet(conn0) == 0);
        REQUIRE(cpd_connection_last(conn0) == conn0);
        REQUIRE(cpd_connection_last(0) == 0);

        // nullptr
        REQUIRE(cpd_connection_count(nullptr) == 0);
        REQUIRE(conn0);

        REQUIRE(cpd_connection_append(0, 0) == 0);
        REQUIRE(cpd_connection_append(0, conn0) == conn0);
        REQUIRE(cpd_connection_append(conn0, 0) == conn0);

        REQUIRE(cpd_canvas_connections(nullptr) == nullptr);
        auto conn1 = cpd_canvas_connections(cnv);
        REQUIRE(cpd_connection_count(conn1) == 1);
        REQUIRE(conn1);
        cpd_connection_list_free(conn1);

        cpd_connection_list_free(conn0);
        cpd_object_free(cnv, obj4);
        cpd_object_free(cnv, obj3);
        cpd_object_free(cnv, obj2);
        cpd_object_free(cnv, obj1);
    }

    cpd_canvas_free(cnv);
}
