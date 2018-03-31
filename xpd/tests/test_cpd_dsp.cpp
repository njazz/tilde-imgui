#include "catch.hpp"

#include "cpd/cpd.h"

#include <string>
#include <thread>

#define SLEEP_MS(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))

static int init = cpd_init();

TEST_CASE("cpd_dsp", "[cpd PureData wrapper]")
{
    SECTION("audio devices")
    {
        auto alist = cpd_audio_devlist_new();

#ifdef __APPLE__
        REQUIRE(cpd_audio_input_devices_num(alist) > 0);
        REQUIRE(cpd_audio_output_devices_num(alist) > 0);

        REQUIRE(cpd_audio_input_device_name(alist, 0) == std::string("Built-in Input"));
        REQUIRE(cpd_audio_output_device_name(alist, 0) == std::string("Built-in Output"));
#endif

        REQUIRE(cpd_audio_input_device_name(alist, 0xFFFF) == std::string());
        REQUIRE(cpd_audio_output_device_name(alist, 0xFFFF) == std::string());

        cpd_audio_devlist_free(alist);

        REQUIRE(cpd_audio_input_devices_num(nullptr) == 0);
        REQUIRE(cpd_audio_output_devices_num(nullptr) == 0);
        REQUIRE(cpd_audio_output_device_name(nullptr, 0) == std::string());
        REQUIRE(cpd_audio_input_device_name(nullptr, 0) == std::string());
    }

    SECTION("dsp test")
    {
        auto cnv = cpd_patch_new();
        auto o1 = cpd_object_new_from_string(cnv, "osc~", "440", 100, 10);
        auto o2 = cpd_object_new(cnv, "dac~", 0, 100, 100);
        cpd_connect(o1, 0, o2, 0);
        cpd_connect(o1, 0, o2, 1);

        REQUIRE(cpd_dsp_thread_start());
        // second attempt
        REQUIRE_FALSE(cpd_dsp_thread_start());
        REQUIRE(cpd_dsp_thread_stop());
        REQUIRE(cpd_dsp_thread_start());

        SLEEP_MS(100);
        REQUIRE(cpd_dsp_switch(1));
        // second time
        REQUIRE_FALSE(cpd_dsp_switch(1));
        SLEEP_MS(300);
        REQUIRE(cpd_dsp_switch(0));
        // second time
        REQUIRE_FALSE(cpd_dsp_switch(0));
        SLEEP_MS(300);
        cpd_dsp_switch(1);
        SLEEP_MS(300);

        REQUIRE(cpd_dsp_thread_stop());
        REQUIRE_FALSE(cpd_dsp_thread_stop());

        cpd_canvas_free(cnv);
    }
}
