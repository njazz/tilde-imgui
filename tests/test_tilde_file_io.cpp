#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "FileParser.h"
#include "LegacyParser.h"
#include "PdStringConverter.h"

#include "mocks/mock_canvas_data.h"
#include "mocks/mock_imgui_mvc.h"
#include "mocks/mock_view_controllers.h"
#include "mocks/mock_views.h"

#include "mocks/mock_app_controller.h"
#include "mocks/mock_common_menus.h"
#include "mocks/mock_grid.h"
#include "mocks/mock_patch_controller.h"
#include "mocks/mock_patch_controller.h"
#include "mocks/mock_patch_menus.h"
#include "mocks/mock_preferences.h"
#include "mocks/mock_uiobject.h"
#include "mocks/mock_undostack.h"

#include "FileSaver.h"

TEST_CASE("view controller stack: basic", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        PdPatchViewControllerStack stack;

        PdCommonMenus m;

        PdPatchViewController pvc1(&m);
        PdPatchViewController pvc2(&m);

        REQUIRE(stack.size() == 0);
        stack.push(&pvc1);
        REQUIRE(stack.size() == 1);
        REQUIRE(stack.last() == &pvc1);
        stack.push(&pvc2);
        REQUIRE(stack.size() == 2);
        REQUIRE(stack.last() == &pvc2);
        stack.pop();
        REQUIRE(stack.size() == 1);
        REQUIRE(stack.last() == &pvc1);
        stack.pop();
        REQUIRE(stack.size() == 0);
    }
}

inline void _legacyTester(std::string src, std::string dest)
{
    std::string ret = "";

    auto src_l = splitStringByToken(src, " ");
    auto l = LegacyParser::convertLegacyString(src_l);

    ret = joinStringWithToken(l, " ");
    ///\todo fix
    ret = ret.substr(0, ret.size() - 1);

    REQUIRE(ret == dest);
}

TEST_CASE("legacy parser", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        _legacyTester("obj 78 84 print", "obj 78 84 print");
        _legacyTester("msg 180 103 msg-box 1 2 3", "obj 180 103 ui.msg msg-box 1 2 3");
        _legacyTester("text 154 206 comment", "obj 154 206 ui.text @Text comment");

        ///\todo atoms - send/receive symbols
        //floatatom 333 114 5 0 0 0 - - -, f 5
        //symbolatom 333 205 10 0 0 0 - - -, f 10

        //obj 81 199 bng 15 250 50 0 empty empty empty 17 7 0 10 -262144 -1
        //-1;
        //obj 85 262 tgl 15 0 empty empty empty 17 7 0 10 -262144 -1 -1 0
        //1;
        //obj 81 327 nbx 5 15 -1e+37 1e+37 0 0 empty empty empty 0 -8 0 10
        //-262144 -1 -1 0 256;
        //obj 230 324 hsl 128 15 0 127 0 0 empty empty empty -2 -8 0 10 -262144
        //-1 -1 0 1;
        //obj 411 257 vsl 15 128 0 127 0 0 empty empty empty 0 -9 0 10 -262144
        //-1 -1 0 1;
        //obj 458 100 hradio 15 1 0 8 empty empty empty 0 -8 0 10 -262144
        //-1 -1 0;
        //obj 504 161 vradio 15 1 0 8 empty empty empty 0 -8 0 10 -262144
        //-1 -1 0;
        //obj 501 346 cnv 15 100 60 empty empty empty 20 12 0 14 -233017 -66577
        //0;
    }
}

TEST_CASE("file parser", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        // TODO
    }
}

TEST_CASE("file saver", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        // TODO
    }
}
