#include "catch.hpp"

#include "cpd/cpd.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_method", "[cpd PureData wrapper]")
{
    SECTION("method_argc")
    {
        REQUIRE(cpd_class_name(nullptr) == std::string(""));

        auto cnv = cpd_patch_new();
        auto obj_f = cpd_object_new(cnv, "f", NULL, 0, 0);

        REQUIRE(cpd_class_method_count(cpd_object_class(obj_f)) == 1);
        REQUIRE(cpd_class_method_at(cpd_object_class(obj_f), 1) == NULL);
        REQUIRE(cpd_class_method_at(cpd_object_class(obj_f), 2) == NULL);
        auto m = cpd_class_method_at(cpd_object_class(obj_f), 0);
        REQUIRE(m);
        REQUIRE(cpd_method_name(m) == std::string("send"));
        REQUIRE(cpd_method_arg_count(m) == 1);
        REQUIRE_FALSE(cpd_method_is_varargs(m));
        REQUIRE(cpd_method_arg_type(m, 0) == CPD_ARG_SYMBOL);

        cpd_canvas_free(cnv);
    }
}
