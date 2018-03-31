#include "catch.hpp"

#include "cpd/cpd.h"

#include <cstdio>
#include <fstream>
#include <string>

#ifndef TEST_DATA_DIR
#define TEST_DATA_DIR "."
#endif

#define TEST_PD_DIR TEST_DATA_DIR "/pd"

static int init = cpd_init();

TEST_CASE("cpd_canvas", "[cpd PureData wrapper]")
{
    SECTION("init")
    {
        REQUIRE(cpd_canvas_current() == 0);
        REQUIRE(cpd_patchlist_count() == 3);
        REQUIRE(cpd_patchlist_last() != 0);

        auto c0 = cpd_patch_new();
        REQUIRE(c0);
        REQUIRE(cpd_canvas_root(c0) == c0);
        REQUIRE(cpd_patchlist_count() == 4);
        REQUIRE(cpd_patchlist_at(0) == c0);
        REQUIRE(cpd_canvas_current() == c0);
        REQUIRE(cpd_canvas_name(c0) == std::string("Untitled-1"));
        REQUIRE(cpd_canvas_object_count(c0) == 0);

        cpd_canvas_free(c0);
        REQUIRE(cpd_patchlist_count() == 3);
    }

    SECTION("multiple")
    {
        REQUIRE(cpd_patchlist_count() == 3);

        auto c0 = cpd_patch_new();
        REQUIRE(cpd_patchlist_count() == 4);
        REQUIRE(c0);
        REQUIRE(cpd_canvas_name(c0) == std::string("Untitled-2"));

        auto c1 = cpd_patch_new();
        REQUIRE(c1);
        REQUIRE(cpd_patchlist_count() == 5);
        REQUIRE(cpd_canvas_name(c1) == std::string("Untitled-3"));

        cpd_canvas_free(c1);
        REQUIRE(cpd_patchlist_count() == 4);

        cpd_canvas_free(c0);
        REQUIRE(cpd_patchlist_count() == 3);
    }

    SECTION("name")
    {
        REQUIRE(cpd_canvas_name(cpd_patchlist_at(0)) == std::string("_float_array_template"));
        REQUIRE(cpd_canvas_name(cpd_patchlist_at(1)) == std::string("_float_template"));
        REQUIRE(cpd_canvas_name(cpd_patchlist_at(2)) == std::string("_text_template"));

        REQUIRE(cpd_canvas_name(nullptr) == nullptr);
    }

    SECTION("root")
    {
        REQUIRE(cpd_canvas_root(nullptr) == nullptr);
        REQUIRE_FALSE(cpd_canvas_is_root(nullptr));
        auto c0 = cpd_patch_new();
        REQUIRE(cpd_canvas_is_root(c0));
        REQUIRE(cpd_canvas_root(c0) == c0);
        cpd_canvas_free(c0);
    }

    SECTION("canvas directory")
    {
        REQUIRE(cpd_patch_dir(nullptr) == std::string());
        auto c0 = cpd_patch_new();
        REQUIRE(cpd_patch_dir(c0) == std::string("~/"));
        cpd_canvas_free(c0);
    }

    SECTION("canvas coords")
    {
        SECTION("root")
        {
            REQUIRE(cpd_patch_xpos(0) == 0);
            REQUIRE(cpd_patch_ypos(0) == 0);
            REQUIRE(cpd_patch_width(0) == 0);
            REQUIRE(cpd_patch_height(0) == 0);
        }
    }

    SECTION("objects")
    {
        REQUIRE(cpd_canvas_object_count(nullptr) == 0);

        auto c0 = cpd_patch_new();
        auto c1 = cpd_patch_new();

        REQUIRE(cpd_canvas_object_count(c0) == 0);
        REQUIRE(cpd_canvas_first_object(c0) == 0);
        auto obj0 = cpd_object_new(c0, "float", 0, 100, 200);
        REQUIRE(cpd_canvas_object_count(c0) == 1);
        REQUIRE(cpd_canvas_first_object(c0) == obj0);

        REQUIRE(cpd_canvas_object_count(c1) == 0);
        REQUIRE(cpd_canvas_first_object(c1) == 0);
        auto obj1 = cpd_object_new(c1, "float", 0, 100, 200);
        REQUIRE(cpd_canvas_object_count(c1) == 1);
        REQUIRE(cpd_canvas_first_object(c1) == obj1);
        auto obj2 = cpd_object_new(c1, "float", 0, 100, 200);
        REQUIRE(cpd_canvas_object_count(c1) == 2);
        REQUIRE(cpd_canvas_first_object(c1) == obj1);

        REQUIRE(cpd_object_next(obj1) == obj2);
        REQUIRE(cpd_object_next(obj2) == nullptr);

        cpd_canvas_free(c0);
        cpd_canvas_free(c1);
    }

    SECTION("first object")
    {
        REQUIRE(cpd_canvas_first_object(0) == nullptr);
    }

    SECTION("load patch")
    {
        auto c0 = cpd_patch_load("not-exists", 0);
        REQUIRE_FALSE(c0);
        c0 = cpd_patch_load("not-exists", "some/dir");
        REQUIRE_FALSE(c0);

        c0 = cpd_patch_load("test_empty_patch.pd", TEST_PD_DIR);
        REQUIRE(c0);
        REQUIRE(cpd_canvas_is_root(c0));
        REQUIRE(cpd_canvas_name(c0) == std::string("test_empty_patch.pd"));
        REQUIRE(cpd_patch_dir(c0) == std::string(TEST_PD_DIR));
        REQUIRE(cpd_canvas_fontsize(c0) == 12);
        REQUIRE(cpd_patch_width(c0) == 700);
        REQUIRE(cpd_patch_height(c0) == 500);
        REQUIRE(cpd_patch_xpos(c0) == 0);
        REQUIRE(cpd_canvas_object_count(c0) == 0);

#ifdef __APPLE__
        REQUIRE(cpd_patch_ypos(c0) == 23);
#endif

        cpd_canvas_free(c0);
    }

    SECTION("load simple core")
    {
        auto c0 = cpd_patch_load("test_patch_core_objects.pd", TEST_PD_DIR);

        REQUIRE(c0);
        REQUIRE(cpd_canvas_object_count(c0) == 7);

        auto obj = cpd_canvas_first_object(c0);

        REQUIRE(obj);
        REQUIRE(cpd_object_name(obj) == std::string("+"));
        obj = cpd_object_next(obj);
        REQUIRE(obj);
        REQUIRE(cpd_object_name(obj) == std::string("message"));
        obj = cpd_object_next(obj);
        REQUIRE(obj);
        REQUIRE(cpd_object_name(obj) == std::string("sqrt"));
        obj = cpd_object_next(obj);
        REQUIRE(obj);
        REQUIRE(cpd_object_name(obj) == std::string("gatom"));
        obj = cpd_object_next(obj);
        REQUIRE(obj);
        REQUIRE(cpd_object_name(obj) == std::string("message"));
        obj = cpd_object_next(obj);
        REQUIRE(obj);
        REQUIRE(cpd_object_name(obj) == std::string("text"));
        obj = cpd_object_next(obj);
        REQUIRE(obj);
        REQUIRE(cpd_object_name(obj) == std::string("gatom"));

        cpd_canvas_free(c0);
    }

    SECTION("load in search paths")
    {
        auto c0 = cpd_patch_load("test_patch_core_objects.pd", NULL);
        REQUIRE_FALSE(c0);

        cpd_searchpath_append("..");
        cpd_searchpath_append(TEST_PD_DIR);
        c0 = cpd_patch_load("test_patch_core_objects.pd", NULL);
        REQUIRE(c0);
        cpd_canvas_free(c0);
    }

    SECTION("current")
    {
        REQUIRE(cpd_canvas_current() != 0);

        auto c0 = cpd_patch_new();
        auto c1 = cpd_patch_new();

        REQUIRE(c0);
        REQUIRE(cpd_canvas_current() == c1);
        cpd_canvas_set_current(c0);
        REQUIRE(cpd_canvas_current() == c0);
        cpd_canvas_set_current(0);
        REQUIRE(cpd_canvas_current() == c0);
        cpd_canvas_unset_current(0);
        REQUIRE(cpd_canvas_current() == c0);
        cpd_canvas_unset_current(c0);
        REQUIRE(cpd_canvas_current() == c1);

        cpd_canvas_free(c1);
        cpd_canvas_free(c0);
    }

    SECTION("to_object")
    {
        REQUIRE(cpd_canvas_to_object(nullptr) == nullptr);

        auto c = cpd_patch_load("simple_abstraction_1.pd", TEST_PD_DIR);
        REQUIRE(c);

        auto obj = cpd_canvas_to_object(c);
        REQUIRE(obj);

        REQUIRE(cpd_object_inlet_count(obj) == 3);
        REQUIRE(cpd_object_inlet_type(obj, 0) == CPD_CONNECTION_SIGNAL);
        REQUIRE(cpd_object_inlet_type(obj, 1) == CPD_CONNECTION_CONTROL);
        REQUIRE(cpd_object_inlet_type(obj, 2) == CPD_CONNECTION_CONTROL);
        // invalid
        REQUIRE(cpd_object_inlet_type(obj, 3) == CPD_CONNECTION_CONTROL);

        REQUIRE(cpd_object_outlet_count(obj) == 2);
        REQUIRE(cpd_object_outlet_type(obj, 0) == CPD_CONNECTION_SIGNAL);
        REQUIRE(cpd_object_outlet_type(obj, 1) == CPD_CONNECTION_CONTROL);
        // invalid
        REQUIRE(cpd_object_outlet_type(obj, 2) == CPD_CONNECTION_CONTROL);

        cpd_canvas_free(c);
    }

    SECTION("types")
    {
        REQUIRE(cpd_object_inlet_type(nullptr, 0) == CPD_CONNECTION_CONTROL);
        REQUIRE(cpd_object_outlet_type(nullptr, 0) == CPD_CONNECTION_CONTROL);
    }

    SECTION("subpatch")
    {
        auto c0 = cpd_patch_new();

        auto s0 = cpd_subpatch_new(c0, "test", 0, 20, 40);
        REQUIRE(s0);
        REQUIRE(cpd_is_canvas(cpd_canvas_to_object(s0)));
        REQUIRE_FALSE(cpd_canvas_is_root(s0));
        REQUIRE(cpd_patch_dir(s0) == std::string());
        REQUIRE(cpd_object_name(cpd_canvas_to_object(s0)) == std::string("canvas"));
        const char* txt = cpd_object_text(cpd_canvas_to_object(s0));
        REQUIRE(txt == std::string("pd test"));
        free((void*)txt);

        // ???? FIX?
        REQUIRE(cpd_canvas_current() == c0);

        REQUIRE(cpd_object_inlet_count(cpd_canvas_to_object(s0)) == 0);
        REQUIRE(cpd_object_outlet_count(cpd_canvas_to_object(s0)) == 0);

        auto obj0 = cpd_object_new_from_string(s0, "inlet", "", 20, 20);

        REQUIRE(cpd_object_inlet_count(cpd_canvas_to_object(s0)) == 1);
        REQUIRE(cpd_object_outlet_count(cpd_canvas_to_object(s0)) == 0);

        auto obj1 = cpd_object_new_from_string(s0, "outlet", "", 20, 200);

        REQUIRE(cpd_canvas_object_count(s0) == 2);

        cpd_object_free(s0, obj0);
        cpd_object_free(s0, obj1);

        cpd_object_free(c0, cpd_canvas_to_object(s0));
        cpd_canvas_free(c0);
    }

    SECTION("subpatch with arguments")
    {
        auto c0 = cpd_patch_new();

        auto args = cpd_list_new_from_string(" a b c 100");
        auto s0 = cpd_subpatch_new(c0, "test", args, 20, 40);
        REQUIRE(cpd_canvas_root(s0) == c0);

        const char* txt = cpd_object_text(cpd_canvas_to_object(s0));
        REQUIRE(txt == std::string("pd test a b c 100"));
        free((void*)txt);

        cpd_object_free(c0, cpd_canvas_to_object(s0));
        cpd_canvas_free(c0);
    }

    SECTION("save")
    {
        REQUIRE_FALSE(cpd_patch_save(0, "", ""));

        auto c0 = cpd_patch_new();

        REQUIRE_FALSE(cpd_patch_save(c0, 0, 0));
        REQUIRE_FALSE(cpd_patch_save(c0, "test", 0));
        REQUIRE_FALSE(cpd_patch_save(c0, 0, "test"));

        auto o0 = cpd_object_new(c0, "loadbang", 0, 40, 50);

        // subpatch begin
        auto sub = cpd_subpatch_new(c0, "sub", 0, 40, 100);
        auto o1 = cpd_object_new(sub, "inlet", 0, 100, 20);
        auto o2 = cpd_object_new_from_string(sub, "f", "200", 20, 70);
        auto o3 = cpd_object_new(sub, "sqrt", 0, 20, 120);
        auto o4 = cpd_object_new(sub, "outlet", 0, 20, 170);
        cpd_connect(o1, 0, o2, 0);
        cpd_connect(o2, 0, o3, 0);
        cpd_connect(o3, 0, o4, 0);
        // subpatch end

        auto o5 = cpd_object_new_from_string(c0, "list", "prepend set", 40, 150);
        auto o6 = cpd_object_new(c0, "print", 0, 40, 200);
        cpd_connect(o0, 0, cpd_canvas_to_object(sub), 0);
        cpd_connect(cpd_canvas_to_object(sub), 0, o5, 0);
        cpd_connect(o5, 0, o6, 0);

        remove("./save_test-1.pd");
        REQUIRE(cpd_patch_save(c0, "save_test-1.pd", "."));

        std::ifstream file("./save_test-1.pd");
        REQUIRE(file);

        cpd_canvas_free(c0);
    }

    SECTION("test at")
    {
        REQUIRE_FALSE(cpd_canvas_object_at(nullptr, 0));

        auto c0 = cpd_patch_new();
        REQUIRE_FALSE(cpd_canvas_object_at(c0, 0));
        REQUIRE_FALSE(cpd_canvas_object_at(c0, 1));

        auto o1 = cpd_object_new(c0, "+", 0, 0, 0);
        auto o2 = cpd_object_new(c0, "*", 0, 0, 0);

        REQUIRE(cpd_canvas_object_at(c0, 0) == o1);
        REQUIRE(cpd_canvas_object_at(c0, 1) == o2);
        REQUIRE(cpd_canvas_object_at(c0, 2) == nullptr);

        cpd_canvas_free(c0);
    }
}
