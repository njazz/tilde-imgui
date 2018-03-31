#include "catch.hpp"

#include "cpd/cpd.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_atom", "[cpd PureData wrapper]")
{
    SECTION("init")
    {
        auto a0 = cpd_atom_float_new(123);
        REQUIRE(cpd_atom_get_float(a0) == 123);
        REQUIRE(cpd_atom_is_float(a0));
        REQUIRE_FALSE(cpd_atom_is_symbol(a0));
        REQUIRE(cpd_atom_get_symbol(a0) == 0);

        cpd_atom_set_float(a0, -200);
        REQUIRE(cpd_atom_get_float(a0) == -200);

        cpd_atom_set_string(a0, "ABC");
        REQUIRE(cpd_atom_get_float(a0) == 0);
        REQUIRE(cpd_symbol_name(cpd_atom_get_symbol(a0)) == std::string("ABC"));

        cpd_atom_free(a0);

        auto a1 = cpd_atom_string_new("XYZ");
        REQUIRE(cpd_atom_is_symbol(a1));
        REQUIRE(cpd_symbol_name(cpd_atom_get_symbol(a1)) == std::string("XYZ"));
        cpd_atom_free(a1);
    }

    SECTION("is")
    {
        REQUIRE_FALSE(cpd_atom_is_float(nullptr));
        REQUIRE_FALSE(cpd_atom_is_symbol(nullptr));

        auto a0 = cpd_atom_float_new(123);
        REQUIRE(cpd_atom_is_float(a0));
        REQUIRE_FALSE(cpd_atom_is_symbol(a0));
        cpd_atom_free(a0);

        auto a1 = cpd_atom_string_new("ABC");
        REQUIRE(cpd_atom_is_symbol(a1));
        REQUIRE_FALSE(cpd_atom_is_float(a1));
        cpd_atom_free(a1);
    }

    SECTION("symbol")
    {
        auto a0 = cpd_atom_float_new(123);
        cpd_atom_set_symbol(a0, cpd_symbol("ABC"));
        REQUIRE(cpd_atom_is_symbol(a0));
        cpd_atom_free(a0);
    }

    SECTION("set")
    {
        REQUIRE_FALSE(cpd_atom_set_float(0, 123));
        REQUIRE_FALSE(cpd_atom_set_symbol(0, cpd_symbol("ABC")));
    }

    SECTION("equal")
    {
        REQUIRE(cpd_atom_equal(nullptr, nullptr));

        auto a0 = cpd_atom_float_new(100);
        auto a1 = cpd_atom_float_new(200);
        auto a2 = cpd_atom_float_new(200);
        auto a3 = cpd_atom_symbol_new(cpd_symbol("ABC"));
        auto a4 = cpd_atom_symbol_new(cpd_symbol("ABC"));
        auto a5 = cpd_atom_symbol_new(cpd_symbol(""));

        REQUIRE_FALSE(cpd_atom_equal(a0, nullptr));
        REQUIRE_FALSE(cpd_atom_equal(nullptr, a0));

        REQUIRE(cpd_atom_equal(a0, a0));
        REQUIRE(cpd_atom_equal(a1, a1));

        REQUIRE_FALSE(cpd_atom_equal(a0, a1));
        REQUIRE_FALSE(cpd_atom_equal(a1, a0));
        REQUIRE_FALSE(cpd_atom_equal(a0, a2));
        REQUIRE(cpd_atom_equal(a1, a2));
        REQUIRE(cpd_atom_equal(a2, a1));

        // different types
        REQUIRE_FALSE(cpd_atom_equal(a2, a3));
        REQUIRE_FALSE(cpd_atom_equal(a3, a2));

        REQUIRE(cpd_atom_equal(a3, a4));
        REQUIRE(cpd_atom_equal(a4, a3));

        REQUIRE_FALSE(cpd_atom_equal(a4, a5));
        REQUIRE_FALSE(cpd_atom_equal(a5, a4));

        REQUIRE_FALSE(cpd_atom_equal(a3, a5));
        REQUIRE_FALSE(cpd_atom_equal(a5, a3));

        cpd_atom_free(a0);
        cpd_atom_free(a1);
        cpd_atom_free(a2);
        cpd_atom_free(a3);
        cpd_atom_free(a4);
        cpd_atom_free(a5);
    }
}
