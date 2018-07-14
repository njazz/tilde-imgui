#include "catch.hpp"

#include "cpd/cpd.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <string>

static std::vector<std::string> global_class_list = { "!=", "%", "&", "&&", "*", "*~",
    "+", "+~", "-", "-~", "/", "/~", "<", "<<", "<=", "==",
    ">", ">=", ">>", "abs", "abs~", "adc~", "append", "array", "array get", "array max", "array min",
    "array quantile", "array random", "array set", "array size", "array sum", "atan", "atan2",
    "b", "bag", "bang~", "bendin", "bendout", "biquad~", "block~", "bp~",
    "catch~", "change", "clip", "clip~", "clone", "cos", "cos~", "cpole~", "cputime",
    "ctlin", "ctlout", "czero_rev~", "czero~",
    "dac~", "dbtopow", "dbtopow~", "dbtorms", "dbtorms~", "declare", "del", "delay", "delread4~",
    "delread~", "delwrite~", "div", "drawcurve", "drawnumber", "drawpolygon", "drawsymbol", "drawtext",
    "element", "env~", "exp", "expr", "expr~", "exp~",
    "f", "fexpr~", "fft~", "filledcurve", "filledpolygon", "framp~", "fswap", "ftom", "ftom~",
    "fudiformat", "fudiparse", "get", "getsize", "hip~", "i", "ifft~", "inlet", "inlet~", "int",
    "key", "keyname", "keyup", "line", "line~", "list append", "list fromsymbol", "list length",
    "list prepend", "list split", "list store", "list tosymbol", "list trim", "loadbang",
    "log", "log~", "lop~", "makefilename", "makenote", "max", "max~", "metro", "midiclkin", "midiin",
    "midiout", "midirealtimein", "min", "min~", "mod", "moses", "mtof", "mtof~",
    "namecanvas", "netreceive", "netsend", "noise~", "notein", "noteout",
    "openpanel", "oscformat", "oscparse", "osc~", "outlet", "outlet~",
    "pack", "page", "pd", "pgmin", "pgmout", "phasor~", "pipe", "plot", "pointer", "poly",
    "polytouchin", "polytouchout", "pow", "powtodb", "powtodb~", "pow~", "print", "print~",
    "q8_rsqrt~", "q8_sqrt~", "qlist",
    "r", "random", "readsf~", "realtime", "receive", "receive~", "rfft~", "rifft~", "rmstodb",
    "rmstodb~", "route", "rpole~", "rsqrt~", "rzero_rev~", "rzero~", "r~",
    "s", "samphold~", "samplerate~", "savepanel", "scalar", "sel", "select", "send", "send~", "set",
    "setsize", "sig~", "sin", "snapshot~", "soundfiler", "spigot", "sqrt", "sqrt~",
    "stripnote", "struct", "swap", "switch~", "sysexin", "s~",
    "t", "table", "tabosc4~", "tabplay~", "tabread", "tabread4", "tabread4~", "tabread~",
    "tabreceive~", "tabsend~", "tabwrite", "tabwrite~", "tan", "template", "text", "text define",
    "text delete", "text fromlist", "text get", "text insert", "text search", "text sequence",
    "text set", "text size", "text tolist", "textfile", "threshold~", "throw~", "timer", "touchin",
    "touchout", "trigger",
    "unpack", "until",
    "v", "value", "vcf~", "vd~", "vline~", "vsnapshot~", "wrap", "wrap~", "writesf~", "|", "||",
    "@receiver object@" };

static int init = cpd_init();

TEST_CASE("cpd_class", "[cpd PureData wrapper]")
{
    SECTION("class_name")
    {
        REQUIRE(cpd_class_name(nullptr) == std::string(""));

        auto cnv = cpd_patch_new();

        auto obj_f = cpd_object_new(cnv, "f", NULL, 0, 0);
        REQUIRE(cpd_class_name(cpd_object_class(obj_f)) == std::string("float"));

        auto obj_f2 = cpd_object_new(cnv, "float", NULL, 0, 0);
        REQUIRE(cpd_class_name(cpd_object_class(obj_f2)) == std::string("float"));

        cpd_canvas_free(cnv);
    }

    SECTION("method_count")
    {
        REQUIRE(cpd_class_method_count(nullptr) == 0);

        auto cnv = cpd_patch_new();

        auto obj_f = cpd_object_new(cnv, "readsf~", NULL, 0, 0);
        REQUIRE(cpd_class_method_count(cpd_object_class(obj_f)) == 5);

        cpd_canvas_free(cnv);
    }

    SECTION("method_at")
    {
        REQUIRE(cpd_class_method_at(nullptr, 0) == 0);

        auto cnv = cpd_patch_new();

        auto obj_f = cpd_object_new(cnv, "readsf~", NULL, 0, 0);
        auto class_f = cpd_object_class(obj_f);
        auto nm = cpd_class_method_count(class_f);
        REQUIRE(nm == 5);
        for (size_t i = 0; i < nm; i++) {
            REQUIRE(cpd_class_method_at(class_f, i) != NULL);
        }

        cpd_canvas_free(cnv);
    }

    SECTION("global class name list")
    {
        auto gl = cpd_class_global_list();
        REQUIRE(gl != 0);
        auto sz = cpd_list_size(gl);
        REQUIRE(sz > 0);
        // TODO:
        // REQUIRE(global_class_list.size() == sz);

        std::vector<std::string> names;
        names.reserve(sz);
        for (size_t i = 0; i < sz; i++) {
            names.push_back(cpd_symbol_name(cpd_list_get_symbol_at(gl, i)));
        }

        std::sort(names.begin(), names.end());
        std::sort(global_class_list.begin(), global_class_list.end());

        REQUIRE(global_class_list == names);

        cpd_list_free(gl);
    }
}
