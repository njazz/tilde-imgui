#include "catch.hpp"

#include "cpd/cpd.h"
#include "cpd/cpd_catcher.h"
#include "cpd/cpd_globals.h"

#include <string>

#ifndef TEST_DATA_DIR
#define TEST_DATA_DIR "."
#endif

#define TEST_PD_DIR TEST_DATA_DIR "/pd"

static int init = cpd_init();

TEST_CASE("cpd_object", "[cpd PureData wrapper]")
{
    SECTION("init")
    {
        auto cnv = cpd_patch_new();
        auto obj1 = cpd_object_new(cnv, "float", 0, 0, 0);
        cpd_object_free(cnv, obj1);
        cpd_canvas_free(cnv);

        // free NULL
        cpd_object_free(cnv, nullptr);
    }

    SECTION("free")
    {
        // nullptr
        cpd_object_free(nullptr, nullptr);
    }

    SECTION("arguments")
    {
        REQUIRE(cpd_object_arguments(0) == nullptr);

        SECTION("empty")
        {
            auto cnv = cpd_patch_new();
            auto obj1 = cpd_object_new(cnv, "float", 0, 0, 0);

            auto args = cpd_object_arguments(obj1);

            REQUIRE(args);
            REQUIRE(cpd_list_size(args) == 0);

            cpd_list_free(args);

            cpd_object_free(cnv, obj1);
            cpd_canvas_free(cnv);
        }

        SECTION("non-empty")
        {
            auto cnv = cpd_patch_new();

            auto in_args = cpd_list_new(0);
            cpd_list_append_float(in_args, 100);
            REQUIRE(cpd_list_size(in_args) == 1);
            REQUIRE(cpd_list_get_float_at(in_args, 0) == 100);

            auto obj1 = cpd_object_new(cnv, "float", in_args, 0, 0);
            cpd_list_free(in_args);

            auto out_args = cpd_object_arguments(obj1);

            REQUIRE(out_args);
            REQUIRE(cpd_list_size(out_args) == 1);
            REQUIRE(cpd_list_get_float_at(out_args, 0) == 100);

            cpd_list_free(out_args);

            cpd_object_free(cnv, obj1);
            cpd_canvas_free(cnv);
        }
    }

    SECTION("help path")
    {
        REQUIRE(cpd_object_help_name(nullptr) == std::string());

        auto cnv = cpd_patch_new();

        // [+]
        auto obj1 = cpd_object_new(cnv, "+", 0, 0, 0);
        REQUIRE(cpd_object_help_name(obj1) == std::string("operators"));
        cpd_object_free(cnv, obj1);

        // [metro]
        auto obj2 = cpd_object_new(cnv, "metro", 0, 0, 0);
        REQUIRE(cpd_object_help_name(obj2) == std::string("metro"));
        cpd_object_free(cnv, obj2);

        cpd_canvas_free(cnv);
    }

    SECTION("help dir")
    {
        REQUIRE(cpd_object_help_dir(nullptr) == std::string());

        auto cnv = cpd_patch_new();

        // [+]
        auto obj1 = cpd_object_new(cnv, "+", 0, 0, 0);
        REQUIRE(cpd_object_help_dir(obj1) == std::string(""));
        cpd_object_free(cnv, obj1);

        // [metro]
        auto obj2 = cpd_object_new(cnv, "metro", 0, 0, 0);
        REQUIRE(cpd_object_help_dir(obj2) == std::string(""));
        cpd_object_free(cnv, obj2);

        cpd_canvas_free(cnv);
    }

    SECTION("text")
    {
        REQUIRE_FALSE(cpd_object_text(nullptr));

        SECTION("no args")
        {
            auto cnv = cpd_patch_new();
            auto obj1 = cpd_object_new(cnv, "float", 0, 0, 0);

            const char* txt = cpd_object_text(obj1);
            REQUIRE(txt == std::string("float"));
            free((void*)txt);

            cpd_object_free(cnv, obj1);
            cpd_canvas_free(cnv);
        }

        SECTION("non-empty")
        {
            auto cnv = cpd_patch_new();
            auto args = cpd_list_new_from_string("100.12 A,Z");
            REQUIRE(cpd_list_size(args) == 4);

            auto obj = cpd_object_new(cnv, "float", args, 0, 0);
            cpd_list_free(args);

            const char* txt = cpd_object_text(obj);
            REQUIRE(txt);
            REQUIRE(txt == std::string("float 100.12 A, Z"));
            free((void*)txt);

            cpd_object_free(cnv, obj);
            cpd_canvas_free(cnv);
        }
    }

    SECTION("position")
    {
        REQUIRE(cpd_object_xpos(nullptr) == -1);
        REQUIRE(cpd_object_ypos(nullptr) == -1);
        cpd_object_set_xpos(nullptr, 0);
        cpd_object_set_ypos(nullptr, 0);

        auto cnv = cpd_patch_new();
        auto obj = cpd_object_new(cnv, "+", 0, 10, 20);

        REQUIRE(cpd_object_xpos(obj) == 10);
        REQUIRE(cpd_object_ypos(obj) == 20);

        cpd_object_set_xpos(obj, 100);
        cpd_object_set_ypos(obj, 200);

        REQUIRE(cpd_object_xpos(obj) == 100);
        REQUIRE(cpd_object_ypos(obj) == 200);

        cpd_object_free(cnv, obj);
        cpd_canvas_free(cnv);
    }

    SECTION("xlets")
    {
        REQUIRE(cpd_object_inlet_count(nullptr) == 0);
        REQUIRE(cpd_object_outlet_count(nullptr) == 0);

        auto cnv = cpd_patch_new();
        auto obj1 = cpd_object_new(cnv, "+", 0, 0, 0);
        auto obj2 = cpd_object_new_from_string(cnv, "route", "a b c", 0, 0);

        REQUIRE(cpd_object_inlet_count(obj1) == 2);
        REQUIRE(cpd_object_outlet_count(obj1) == 1);

        REQUIRE(cpd_object_inlet_count(obj2) == 1);
        REQUIRE(cpd_object_outlet_count(obj2) == 4);

        cpd_object_free(cnv, obj1);
        cpd_object_free(cnv, obj2);
        cpd_canvas_free(cnv);
    }

    SECTION("connect")
    {
        auto cnv = cpd_patch_new();
        auto obj1 = cpd_object_new(cnv, "+", 0, 0, 0);
        auto obj2 = cpd_object_new_from_string(cnv, "route", "a b c", 0, 0);

        REQUIRE(cpd_object_inlet_count(obj1) == 2);
        REQUIRE(cpd_object_outlet_count(obj1) == 1);

        // self-connection
        REQUIRE_FALSE(cpd_connect(obj1, 0, obj1, 0));
        // NULL
        REQUIRE_FALSE(cpd_connect(obj1, 0, nullptr, 0));
        REQUIRE_FALSE(cpd_connect(nullptr, 0, obj1, 0));
        REQUIRE_FALSE(cpd_connect(nullptr, 0, nullptr, 0));

        // invalid outlet
        REQUIRE_FALSE(cpd_connect(obj1, 1, obj2, 0));
        // invalid inlet
        REQUIRE_FALSE(cpd_connect(obj1, 0, obj2, 1));

        REQUIRE(cpd_connect(obj1, 0, obj2, 0));
        REQUIRE(cpd_connect(obj2, 3, obj1, 0));

        REQUIRE(cpd_object_inlet_count(obj2) == 1);
        REQUIRE(cpd_object_outlet_count(obj2) == 4);

        cpd_object_free(cnv, obj1);
        cpd_object_free(cnv, obj2);
        cpd_canvas_free(cnv);
    }

    SECTION("is_abstraction")
    {
        REQUIRE_FALSE(cpd_is_abstraction(nullptr));
        auto cnv = cpd_patch_load("subpatch_abstraction_1.pd", TEST_PD_DIR);
        REQUIRE(cnv);

        auto obj = cpd_canvas_object_at(cnv, 0);
        REQUIRE(obj);
        REQUIRE_FALSE(cpd_is_abstraction(obj));
        REQUIRE_FALSE(cpd_is_abstraction(cpd_canvas_object_at(cnv, 4)));
        const char* name = cpd_object_text(obj);
        REQUIRE(name == std::string("pd gen~"));
        free((void*)name);

        cpd_canvas_free(cnv);

        auto cnv2 = cpd_patch_load("test_abstraction_1.pd", TEST_PD_DIR);
        REQUIRE(cnv2);
        REQUIRE(cpd_canvas_object_count(cnv2) == 1);
        obj = cpd_canvas_object_at(cnv2, 0);
        REQUIRE(obj);
        REQUIRE(cpd_is_abstraction(obj));
        REQUIRE(cpd_object_inlet_count(obj) == 3);
        REQUIRE(cpd_object_outlet_count(obj) == 2);
        REQUIRE(cpd_object_abstraction_filename(obj) == std::string("simple_abstraction_1.pd"));
        REQUIRE(cpd_object_abstraction_dir(obj) == std::string(TEST_PD_DIR));

        REQUIRE(cpd_object_abstraction_filename(nullptr) == std::string());
        REQUIRE(cpd_object_abstraction_dir(nullptr) == std::string());

        cpd_canvas_free(cnv2);
    }

    SECTION("create abstraction")
    {
        auto cnv = cpd_patch_new();

        // no search path
        auto abs0 = cpd_object_new(cnv, "simple_abstraction_1", 0, 0, 0);
        REQUIRE_FALSE(abs0);

        // full path
        auto abs1 = cpd_object_new(cnv, TEST_PD_DIR "/simple_abstraction_1", 0, 0, 0);
        REQUIRE(abs1);
        REQUIRE(cpd_is_abstraction(abs1));

        cpd_searchpath_append(TEST_PD_DIR);

        cpd_canvas_free(cnv);
    }

    SECTION("list methods")
    {
        REQUIRE_FALSE(cpd_object_method_names(nullptr));

        auto cnv = cpd_patch_new();

        auto obj = cpd_object_new(cnv, "soundfiler", 0, 0, 0);
        auto methods = cpd_object_method_names(obj);
        REQUIRE(cpd_list_size(methods) == 2);
        REQUIRE(cpd_symbol_name(cpd_list_get_symbol_at(methods, 0)) == std::string("read"));
        REQUIRE(cpd_symbol_name(cpd_list_get_symbol_at(methods, 1)) == std::string("write"));

        cpd_list_free(methods);

        cpd_canvas_free(cnv);
    }

    SECTION("bind")
    {
        cpd_catcher_init();

        REQUIRE_FALSE(cpd_symbol_binded(NULL));
        REQUIRE(cpd_symbol_binded(CPD_SYMBOL_PD));

        auto cnv = cpd_patch_new();

        auto catcher = cpd_catcher_new(cnv);
        t_cpd_symbol* DEST = cpd_symbol("send_bind");
        REQUIRE_FALSE(cpd_symbol_binded(DEST));
        cpd_bind_object(catcher, DEST);
        REQUIRE(cpd_symbol_binded(DEST));

        auto args = cpd_list_new(0);
        cpd_list_append_float(args, 200);

        REQUIRE_FALSE(cpd_send_brodcast_message(0, args));
        REQUIRE_FALSE(cpd_send_brodcast_message(cpd_symbol("XXunknown"), 0));
        REQUIRE_FALSE(cpd_send_brodcast_message(cpd_symbol("XXunknown"), args));

        REQUIRE(cpd_send_brodcast_message(DEST, args));
        cpd_list_free(args);

        REQUIRE(cpd_catcher_count(catcher) == 1);
        REQUIRE(cpd_list_to_string(cpd_catcher_last(catcher)) == std::string("send_bind 200"));

        auto catcher2 = cpd_catcher_new(cnv);
        cpd_bind_object(catcher2, DEST);

        args = cpd_list_new_from_string("a b c");
        REQUIRE(cpd_send_brodcast_message(DEST, args));
        REQUIRE(cpd_list_to_string(cpd_catcher_last(catcher)) == std::string("send_bind a b c"));
        cpd_list_free(args);

        cpd_canvas_free(cnv);
    }
}
