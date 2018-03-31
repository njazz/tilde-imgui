#include "catch.hpp"

#include "cpd/cpd.h"
#include "cpd/cpd_catcher.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_array", "[cpd PureData wrapper]")
{
    SECTION("create")
    {
        auto cnv = cpd_patch_new();
        auto arr = cpd_array_new(cnv, cpd_symbol("array1"), 200, 0);
        REQUIRE(cpd_array_size(arr) == 200);
        REQUIRE(cpd_array_find_by_name(cpd_symbol("array1")) == arr);
        REQUIRE(cpd_array_find_by_name(cpd_symbol("unknown")) == NULL);
        REQUIRE(cpd_array_name(arr) == cpd_symbol("array1"));
        cpd_array_free(cnv, arr);

        cpd_array_free(NULL, arr);
        cpd_array_free(cnv, NULL);
        REQUIRE(cpd_array_name(NULL) == cpd_symbol(""));

        REQUIRE(cpd_array_new(NULL, cpd_symbol("array1"), 200, 0) == nullptr);
        cpd_canvas_free(cnv);
    }

    SECTION("size")
    {
        auto cnv = cpd_patch_new();
        auto arr = cpd_array_new(cnv, cpd_symbol("array1"), 0, 0);
        REQUIRE(cpd_array_size(arr) == 1);
        REQUIRE(cpd_array_size(NULL) == 0);
        cpd_canvas_free(cnv);
    }

    SECTION("linewidth")
    {
        REQUIRE(cpd_array_linewidth(NULL) == 0);
        REQUIRE(cpd_array_set_linewidth(NULL, 0) == 0);
        REQUIRE(cpd_array_set_plotstyle(NULL, CPD_ARRAY_STYLE_POLY) == 0);

        auto cnv = cpd_patch_new();

        auto arr1 = cpd_array_new(cnv, cpd_symbol("array1"), 0, 0);
        REQUIRE(cpd_array_linewidth(arr1) == 1);

        auto arr2 = cpd_array_new(cnv, cpd_symbol("array2"), 100, CPD_ARRAY_STYLE_POLY);
        REQUIRE(cpd_array_linewidth(arr2) == 2);
        REQUIRE(cpd_array_plotstyle(arr2) == CPD_ARRAY_STYLE_POLY);

        auto arr3 = cpd_array_new(cnv, cpd_symbol("array3"), 100, CPD_ARRAY_STYLE_POINTS);
        REQUIRE(cpd_array_linewidth(arr3) == 1);
        REQUIRE(cpd_array_plotstyle(arr3) == CPD_ARRAY_STYLE_POINTS);

        auto arr4 = cpd_array_new(cnv, cpd_symbol("array4"), 100, CPD_ARRAY_STYLE_BEZIER);
        REQUIRE(cpd_array_linewidth(arr4) == 1);
        REQUIRE(cpd_array_plotstyle(arr4) == CPD_ARRAY_STYLE_BEZIER);

        REQUIRE(cpd_array_set_linewidth(arr4, 1.2));
        REQUIRE(cpd_array_linewidth(arr4) == 1.2f);

        REQUIRE(cpd_array_set_plotstyle(arr4, CPD_ARRAY_STYLE_POINTS));
        REQUIRE(cpd_array_plotstyle(arr4) == CPD_ARRAY_STYLE_POINTS);

        REQUIRE(cpd_array_set_plotstyle(arr4, CPD_ARRAY_STYLE_POLY));
        REQUIRE(cpd_array_plotstyle(arr4) == CPD_ARRAY_STYLE_POLY);

        REQUIRE(cpd_array_set_plotstyle(arr4, CPD_ARRAY_STYLE_BEZIER));
        REQUIRE(cpd_array_plotstyle(arr4) == CPD_ARRAY_STYLE_BEZIER);

        REQUIRE(cpd_array_set_plotstyle(arr4, CPD_ARRAY_HIDE_NAME) == 0);

        cpd_canvas_free(cnv);
    }

    SECTION("hidden name")
    {
        REQUIRE(cpd_array_hidden_name(NULL) == 0);

        auto cnv = cpd_patch_new();

        auto arr1 = cpd_array_new(cnv, cpd_symbol("array1"), 100, 0);
        REQUIRE(cpd_array_hidden_name(arr1) == 0);

        auto arr2 = cpd_array_new(cnv, cpd_symbol("array2"), 100, CPD_ARRAY_HIDE_NAME);
        REQUIRE(cpd_array_hidden_name(arr2) == 1);

        cpd_canvas_free(cnv);
    }

    SECTION("same name")
    {
        REQUIRE(cpd_array_hidden_name(NULL) == 0);

        auto cnv = cpd_patch_new();

        auto arr1 = cpd_array_new(cnv, cpd_symbol("same"), 100, 0);
        auto arr2 = cpd_array_new(cnv, cpd_symbol("same"), 100, 0);
        REQUIRE(arr1);
        REQUIRE(arr2);
        REQUIRE(arr1 != arr2);

        REQUIRE(cpd_array_find_by_name(cpd_symbol("same")) == arr1);

        cpd_canvas_free(cnv);
    }

    SECTION("elements")
    {
        SECTION("copy_to")
        {
            auto cnv = cpd_patch_new();
            auto arr = cpd_array_new(cnv, cpd_symbol("array1"), 5, 0);

            REQUIRE(cpd_array_float_at(arr, 0) == 0);
            REQUIRE(cpd_array_float_at(arr, 1) == 0);
            REQUIRE(cpd_array_float_at(arr, 2) == 0);
            REQUIRE(cpd_array_float_at(arr, 3) == 0);
            REQUIRE(cpd_array_float_at(arr, 4) == 0);

            t_cpd_float buf[3] = { 1, 2, 3 };
            cpd_elements_copy_floats_to(cpd_array_element_at(arr, 0), buf, 3);

            REQUIRE(buf[0] == 0);
            REQUIRE(buf[1] == 0);
            REQUIRE(buf[2] == 0);

            cpd_array_set_float_at(arr, 2, 100);
            cpd_array_set_float_at(arr, 3, 200);
            cpd_array_set_float_at(arr, 4, 300);

            REQUIRE(cpd_array_float_at(arr, 0) == 0);
            REQUIRE(cpd_array_float_at(arr, 1) == 0);
            REQUIRE(cpd_array_float_at(arr, 2) == 100);
            REQUIRE(cpd_array_float_at(arr, 3) == 200);
            REQUIRE(cpd_array_float_at(arr, 4) == 300);

            cpd_elements_copy_floats_to(cpd_array_element_at(arr, 2), buf, 3);

            REQUIRE(buf[0] == 100);
            REQUIRE(buf[1] == 200);
            REQUIRE(buf[2] == 300);

            cpd_canvas_free(cnv);
        }

        SECTION("copy_from")
        {
            auto cnv = cpd_patch_new();
            auto arr = cpd_array_new(cnv, cpd_symbol("array2"), 5, 0);

            REQUIRE(cpd_array_float_at(arr, 0) == 0);
            REQUIRE(cpd_array_float_at(arr, 1) == 0);
            REQUIRE(cpd_array_float_at(arr, 2) == 0);
            REQUIRE(cpd_array_float_at(arr, 3) == 0);
            REQUIRE(cpd_array_float_at(arr, 4) == 0);

            t_cpd_float buf[] = { 100, 200, 300 };
            cpd_elements_copy_floats_from(cpd_array_element_at(arr, 0), buf, 3);

            REQUIRE(cpd_array_float_at(arr, 0) == 100);
            REQUIRE(cpd_array_float_at(arr, 1) == 200);
            REQUIRE(cpd_array_float_at(arr, 2) == 300);
            REQUIRE(cpd_array_float_at(arr, 3) == 0);
            REQUIRE(cpd_array_float_at(arr, 4) == 0);

            cpd_canvas_free(cnv);
        }

        SECTION("map")
        {
            auto cnv = cpd_patch_new();
            auto arr = cpd_array_new(cnv, cpd_symbol("array3"), 5, 0);

            cpd_array_set_float_at(arr, 0, 1);
            cpd_array_set_float_at(arr, 1, 2);
            cpd_array_set_float_at(arr, 2, 3);
            cpd_array_set_float_at(arr, 3, 4);

            cpd_elements_map(cpd_array_element_at(arr, 0), 4, [](t_cpd_float v) { return v * v; });

            REQUIRE(cpd_array_float_at(arr, 0) == 1);
            REQUIRE(cpd_array_float_at(arr, 1) == 4);
            REQUIRE(cpd_array_float_at(arr, 2) == 9);
            REQUIRE(cpd_array_float_at(arr, 3) == 16);
            REQUIRE(cpd_array_float_at(arr, 4) == 0);

            cpd_canvas_free(cnv);
        }

        SECTION("fold")
        {
            auto cnv = cpd_patch_new();
            auto arr = cpd_array_new(cnv, cpd_symbol("array3"), 5, 0);

            cpd_array_set_float_at(arr, 0, 0);
            cpd_array_set_float_at(arr, 1, 1);
            cpd_array_set_float_at(arr, 2, 2);
            cpd_array_set_float_at(arr, 3, 3);
            cpd_array_set_float_at(arr, 4, 4);

            auto diff = [](t_cpd_float v1, t_cpd_float v2) { return v1 - v2; };

            auto lv = cpd_elements_lfold(cpd_array_element_at(arr, 0), 4, diff, 0);
            auto rv = cpd_elements_rfold(cpd_array_element_at(arr, 0), 4, diff, 0);

            // ((((0 - 0) - 1) - 2) - 3)
            REQUIRE(lv == -6);
            // (0 - (1 - (2 - (3 - 0))))
            REQUIRE(rv == -2);

            auto add = [](t_cpd_float v1, t_cpd_float v2) { return v1 + v2; };

            lv = cpd_elements_lfold(cpd_array_element_at(arr, 0), 4, add, 0);
            rv = cpd_elements_rfold(cpd_array_element_at(arr, 0), 4, add, 0);
            REQUIRE(lv == 6);
            REQUIRE(rv == 6);

            lv = cpd_elements_lfold(cpd_array_element_at(arr, 0), 4, add, 10);
            rv = cpd_elements_rfold(cpd_array_element_at(arr, 0), 4, add, 10);
            REQUIRE(lv == 16);
            REQUIRE(rv == 16);

            auto mul = [](t_cpd_float v1, t_cpd_float v2) { return v1 * v2; };

            lv = cpd_elements_lfold(cpd_array_element_at(arr, 1), 4, mul, 1);
            rv = cpd_elements_rfold(cpd_array_element_at(arr, 1), 4, mul, 1);
            REQUIRE(lv == 24);
            REQUIRE(rv == 24);

            cpd_canvas_free(cnv);
        }

        SECTION("fill")
        {
            auto cnv = cpd_patch_new();
            auto arr = cpd_array_new(cnv, cpd_symbol("array4"), 3, 0);

            REQUIRE(cpd_array_float_at(arr, 0) == 0);
            REQUIRE(cpd_array_float_at(arr, 1) == 0);
            REQUIRE(cpd_array_float_at(arr, 2) == 0);

            cpd_elements_fill(cpd_array_element_at(arr, 0), 100, 3);

            REQUIRE(cpd_array_float_at(arr, 0) == 100);
            REQUIRE(cpd_array_float_at(arr, 1) == 100);
            REQUIRE(cpd_array_float_at(arr, 2) == 100);

            cpd_canvas_free(cnv);
        }
    }

    SECTION("data")
    {
        REQUIRE(cpd_array_element_at(NULL, 0) == NULL);

        auto cnv = cpd_patch_new();
        auto arr = cpd_array_new(cnv, cpd_symbol("array1"), 5, 0);

        // no NULL or bounds checks
        REQUIRE(cpd_array_float_at(arr, 0) == 0);
        REQUIRE(cpd_array_float_at(arr, 1) == 0);
        REQUIRE(cpd_array_float_at(arr, 2) == 0);
        REQUIRE(cpd_array_float_at(arr, 3) == 0);
        REQUIRE(cpd_array_float_at(arr, 4) == 0);

        REQUIRE(cpd_array_element_at(arr, 5) == NULL);
        REQUIRE(cpd_array_element_at(arr, 6) == NULL);

        cpd_array_set_float_at(arr, 0, 1);
        cpd_array_set_float_at(arr, 1, 2);
        cpd_array_set_float_at(arr, 2, 3);
        cpd_array_set_float_at(arr, 3, 4);
        cpd_array_set_float_at(arr, 4, 5);

        REQUIRE(cpd_array_float_at(arr, 0) == 1.f);
        REQUIRE(cpd_array_float_at(arr, 1) == 2.f);
        REQUIRE(cpd_array_float_at(arr, 2) == 3.f);
        REQUIRE(cpd_array_float_at(arr, 3) == 4.f);
        REQUIRE(cpd_array_float_at(arr, 4) == 5.f);

        cpd_canvas_free(cnv);
    }

    SECTION("copy data")
    {
        REQUIRE_FALSE(cpd_array_copy_to(NULL, 0, 5));
        REQUIRE_FALSE(cpd_array_copy_from(NULL, 0, 5));

        t_cpd_float buf[5] = { 1, 1, 1, 1, 1 };

        auto cnv = cpd_patch_new();
        auto arr = cpd_array_new(cnv, cpd_symbol("array1"), 3, 0);
        REQUIRE(cpd_array_copy_to(arr, buf, 5));

        // copy only 3 first elements
        REQUIRE(buf[0] == 0);
        REQUIRE(buf[1] == 0);
        REQUIRE(buf[2] == 0);
        REQUIRE(buf[3] == 1);
        REQUIRE(buf[4] == 1);

        t_cpd_float buf2[2] = { 2, 2 };
        REQUIRE(cpd_array_copy_from(arr, buf2, 2));

        REQUIRE(cpd_array_copy_to(arr, buf, 5));
        // copy only 3 first elements
        REQUIRE(buf[0] == 2);
        REQUIRE(buf[1] == 2);
        REQUIRE(buf[2] == 0);
        REQUIRE(buf[3] == 1);
        REQUIRE(buf[4] == 1);

        cpd_canvas_free(cnv);
    }

    SECTION("pointers")
    {
        auto cnv = cpd_patch_new();
        auto arr = cpd_array_new(cnv, cpd_symbol("array1"), 3, 0);

        auto ptr = cpd_array_element_at(arr, 0);

        for (size_t i = 0; i < 3; i++) {
            REQUIRE(cpd_element_float(ptr) == 0);
            cpd_element_set_float(ptr, i);
            REQUIRE(cpd_element_float(ptr) == i);

            ptr = cpd_element_next(ptr);
        }

        ptr = cpd_array_element_at(arr, 2);
        for (size_t i = 3; i > 0; i--) {
            REQUIRE(cpd_element_float(ptr) == i - 1);
            ptr = cpd_element_prev(ptr);
        }

        REQUIRE(cpd_element_float(cpd_element_move(cpd_array_element_at(arr, 0), 2)) == 2);

        cpd_canvas_free(cnv);
    }

    SECTION("resize")
    {
        REQUIRE_FALSE(cpd_array_resize(NULL, 100));

        auto cnv = cpd_patch_new();
        auto arr = cpd_array_new(cnv, cpd_symbol("array1"), 3, 0);

        REQUIRE_FALSE(cpd_array_resize(arr, 0));
        REQUIRE(cpd_array_resize(arr, 3));

        cpd_elements_fill(cpd_array_element_at(arr, 0), 1000, 3);

        REQUIRE(cpd_array_float_at(arr, 0) == 1000);
        REQUIRE(cpd_array_float_at(arr, 1) == 1000);
        REQUIRE(cpd_array_float_at(arr, 2) == 1000);

        REQUIRE(cpd_array_resize(arr, 5));

        REQUIRE(cpd_array_float_at(arr, 0) == 1000);
        REQUIRE(cpd_array_float_at(arr, 1) == 1000);
        REQUIRE(cpd_array_float_at(arr, 2) == 1000);
        REQUIRE(cpd_array_float_at(arr, 3) == 0);
        REQUIRE(cpd_array_float_at(arr, 4) == 0);

        REQUIRE(cpd_array_resize(arr, 2));

        REQUIRE(cpd_array_float_at(arr, 0) == 1000);
        REQUIRE(cpd_array_float_at(arr, 1) == 1000);

        cpd_canvas_free(cnv);
    }
}
