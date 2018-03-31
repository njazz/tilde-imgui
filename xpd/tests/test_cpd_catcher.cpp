#include "catch.hpp"

#include "cpd/cpd.h"
#include "cpd/cpd_catcher.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_catcher", "[cpd PureData wrapper]")
{
    SECTION("init")
    {
        REQUIRE_FALSE(cpd_is_catcher(0));

        auto cnv = cpd_patch_new();
        REQUIRE_FALSE(cpd_catcher_new(cnv));

        cpd_catcher_init();
        cpd_catcher_init();

        REQUIRE_FALSE(cpd_is_catcher(0));

        // non-catcher
        auto non_catcher = cpd_object_new(cnv, "+", 0, 0, 0);
        REQUIRE_FALSE(cpd_is_catcher(non_catcher));
        cpd_object_free(cnv, non_catcher);

        REQUIRE_FALSE(cpd_catcher_new(nullptr));

        // catcher
        auto catcher = cpd_catcher_new(cnv);
        REQUIRE(cpd_is_catcher(catcher));

        // empty
        REQUIRE(cpd_catcher_empty(catcher));
        REQUIRE_FALSE(cpd_catcher_empty(nullptr));

        // size
        REQUIRE(cpd_catcher_count(catcher) == 0);
        REQUIRE(cpd_catcher_count(nullptr) == 0);

        // last
        REQUIRE(cpd_catcher_last(catcher) == nullptr);
        REQUIRE(cpd_catcher_last(nullptr) == nullptr);

        // clear
        cpd_catcher_clear(catcher);
        cpd_catcher_clear(nullptr);

        // at
        REQUIRE(cpd_catcher_at(catcher, 0) == nullptr);
        REQUIRE(cpd_catcher_at(nullptr, 0) == nullptr);

        // last bang
        REQUIRE_FALSE(cpd_catcher_last_bang(catcher));
        REQUIRE_FALSE(cpd_catcher_last_bang(nullptr));

        cpd_object_free(cnv, catcher);
        cpd_canvas_free(cnv);
    }

    SECTION("bang")
    {
        auto cnv = cpd_patch_new();
        auto catcher = cpd_catcher_new(cnv);

        cpd_send_bang(nullptr);
        cpd_send_bang(catcher);
        REQUIRE_FALSE(cpd_catcher_empty(catcher));
        REQUIRE(cpd_catcher_count(catcher) == 1);
        REQUIRE(cpd_catcher_last(catcher));
        REQUIRE(cpd_catcher_at(catcher, 0));
        REQUIRE(cpd_catcher_at(catcher, 1) == nullptr);
        REQUIRE(cpd_catcher_last_bang(catcher));

        cpd_catcher_pop(catcher);
        REQUIRE(cpd_catcher_empty(catcher));
        cpd_catcher_pop(catcher);
        REQUIRE(cpd_catcher_empty(catcher));

        cpd_object_free(cnv, catcher);
        cpd_canvas_free(cnv);
    }

    SECTION("float")
    {
        auto cnv = cpd_patch_new();
        auto catcher = cpd_catcher_new(cnv);

        cpd_send_float(nullptr, 1000);

        // catcher empty
        REQUIRE_FALSE(cpd_catcher_last_float(catcher, 1000));

        cpd_send_float(catcher, 1000);
        REQUIRE(cpd_catcher_last_float(catcher, 1000));
        REQUIRE_FALSE(cpd_catcher_last_float(nullptr, 1000));

        cpd_catcher_clear(catcher);
        REQUIRE(cpd_catcher_empty(catcher));
        cpd_catcher_clear(catcher);
        REQUIRE(cpd_catcher_empty(catcher));

        cpd_send_float(catcher, 2000);
        REQUIRE(cpd_catcher_last_float(catcher, 2000));

        cpd_send_float(catcher, 3000);
        REQUIRE(cpd_catcher_last_float(catcher, 3000));

        cpd_catcher_pop(catcher);
        cpd_catcher_pop(nullptr);
        REQUIRE(cpd_catcher_last_float(catcher, 2000));

        cpd_object_free(cnv, catcher);
        cpd_canvas_free(cnv);
    }

    SECTION("symbol")
    {
        auto cnv = cpd_patch_new();
        auto catcher = cpd_catcher_new(cnv);

        // invalid
        cpd_send_symbol(nullptr, cpd_symbol("ABC"));
        cpd_send_symbol(nullptr, nullptr);
        cpd_send_symbol(catcher, nullptr);

        // catcher empty
        REQUIRE_FALSE(cpd_catcher_last_symbol(catcher, "ABC"));

        // valid
        cpd_send_symbol(catcher, cpd_symbol("ABC"));
        REQUIRE(cpd_catcher_count(catcher) == 1);
        REQUIRE(cpd_catcher_last_symbol(catcher, "ABC"));

        cpd_send_symbol(catcher, cpd_symbol("DEF"));
        REQUIRE(cpd_catcher_count(catcher) == 2);
        REQUIRE(cpd_catcher_last_symbol(catcher, "DEF"));

        cpd_object_free(cnv, catcher);
        cpd_canvas_free(cnv);
    }

    SECTION("list")
    {
        auto cnv = cpd_patch_new();
        auto catcher = cpd_catcher_new(cnv);

        auto l0 = cpd_list_new_from_string("1 2 3");
        auto l1 = cpd_list_new_from_string("A B C");
        auto l2 = cpd_list_new_from_string("1.234");
        auto l3 = cpd_list_new(0);

        // invalid
        cpd_send_list(nullptr, l0);
        cpd_send_list(nullptr, nullptr);
        cpd_send_list(catcher, nullptr);

        // catcher empty
        REQUIRE_FALSE(cpd_catcher_last_list(catcher, l0));

        // valid
        cpd_send_list(catcher, l0);
        REQUIRE(cpd_catcher_count(catcher) == 1);
        REQUIRE(cpd_catcher_last_list(catcher, l0));
        REQUIRE_FALSE(cpd_catcher_last_list(catcher, l1));
        REQUIRE_FALSE(cpd_catcher_last_list(catcher, l2));

        cpd_list_free(l0);
        cpd_list_free(l1);
        cpd_list_free(l2);
        cpd_list_free(l3);
        cpd_object_free(cnv, catcher);
        cpd_canvas_free(cnv);
    }

    SECTION("message")
    {
        auto cnv = cpd_patch_new();
        auto catcher = cpd_catcher_new(cnv);

        auto l0 = cpd_list_new_from_string("1 2 3");
        auto l1 = cpd_list_new_from_string("A B C");
        auto l2 = cpd_list_new_from_string("1.234");
        auto l3 = cpd_list_new(0);

        // invalid
        cpd_send_message(nullptr, cpd_symbol("test"), l0);
        cpd_send_message(catcher, nullptr, l0);
        cpd_send_message(catcher, cpd_symbol("test"), nullptr);
        cpd_send_message(nullptr, nullptr, l0);
        cpd_send_message(nullptr, cpd_symbol("test"), nullptr);
        cpd_send_message(catcher, nullptr, nullptr);
        cpd_send_message(nullptr, nullptr, nullptr);

        // catcher empty
        REQUIRE(cpd_catcher_count(catcher) == 0);
        REQUIRE_FALSE(cpd_catcher_last_message(catcher, "test", l0));

        // valid
        cpd_send_message(catcher, cpd_symbol("test"), l0);
        REQUIRE(cpd_catcher_count(catcher) == 1);
        REQUIRE(cpd_catcher_last_message(catcher, "test", l0));
        REQUIRE_FALSE(cpd_catcher_last_message(catcher, "test", l1));
        REQUIRE_FALSE(cpd_catcher_last_message(catcher, "test", l2));

        cpd_list_free(l0);
        cpd_list_free(l1);
        cpd_list_free(l2);
        cpd_list_free(l3);
        cpd_object_free(cnv, catcher);
        cpd_canvas_free(cnv);
    }

    SECTION("text")
    {
        auto cnv = cpd_patch_new();
        auto catcher = cpd_catcher_new(cnv);

        // empty catcher
        REQUIRE_FALSE(cpd_catcher_last_string(catcher, "test"));
        REQUIRE_FALSE(cpd_catcher_last_string(nullptr, "test"));

        cpd_send_bang(catcher);
        REQUIRE(cpd_catcher_last_string(catcher, "bang"));

        cpd_send_float(catcher, 1000);
        REQUIRE(cpd_catcher_last_string(catcher, "float 1000"));

        cpd_send_symbol(catcher, cpd_symbol("ABC"));
        REQUIRE(cpd_catcher_last_string(catcher, "symbol ABC"));

        cpd_object_free(cnv, catcher);
        cpd_canvas_free(cnv);
    }
}
