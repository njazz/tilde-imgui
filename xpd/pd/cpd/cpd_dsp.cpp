#include "cpd_dsp.h"
#include "cpd_globals.h"
#include "cpd_list.h"
#include "pr_log.h"

#include "m_pd.h"
extern "C" {
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"
}

#include <string>
#include <thread>
#include <vector>

int cpd_dsp_switch(int state)
{
    if (!pd_this) {
        ERROR("library is not initialized yet");
        return 0;
    }

    if (state && THISGUI->i_dspstate) {
        DEBUG("DSP is already ON");
        return 0;
    }

    if (!state && !THISGUI->i_dspstate) {
        DEBUG("DSP is already OFF");
        return 0;
    }

    t_pd* dest = CPD_SYMBOL_PD->s_thing;

    if (dest == NULL) {
        ERROR("Pd object not found");
        return 0;
    }

    t_atom a;
    SETFLOAT(&a, state ? 1 : 0);
    DEBUG("DSP {}", state ? "ON" : "OFF");
    pd_typedmess(dest, gensym("dsp"), 1, &a);
    return 1;
}

struct _cpd_audio_devlist {
    std::vector<std::string> in_devices;
    std::vector<std::string> out_devices;
    bool can_callback;
    bool can_multi;

    _cpd_audio_devlist()
        : can_callback(false)
        , can_multi(false)
    {
        update();
    }

    void update()
    {
        static const int MAX_NUM_DEV = 32;
        static const int DESC_SIZE = 256;

        char indevlist[MAX_NUM_DEV][DESC_SIZE];
        char outdevlist[MAX_NUM_DEV][DESC_SIZE];
        int nindevs = 0;
        int noutdevs = 0;
        int canmulti = 0;
        int cancallback = 0;

        sys_get_audio_devs(
            (char*)indevlist, &nindevs,
            (char*)outdevlist, &noutdevs,
            &canmulti, &cancallback,
            MAX_NUM_DEV, DESC_SIZE);

        can_callback = cancallback;
        can_multi = canmulti;

        for (int i = 0; i < nindevs; i++)
            in_devices.push_back(indevlist[i]);

        for (int i = 0; i < noutdevs; i++)
            out_devices.push_back(outdevlist[i]);
    }
};

t_cpd_audio_devlist* cpd_audio_devlist_new()
{
    return new t_cpd_audio_devlist;
}

void cpd_audio_devlist_free(t_cpd_audio_devlist* l)
{
    delete l;
}

size_t cpd_audio_input_devices_num(t_cpd_audio_devlist* devl)
{
    if (!devl) {
        DEBUG("NULL given");
        return 0;
    }

    return devl->in_devices.size();
}

size_t cpd_audio_output_devices_num(t_cpd_audio_devlist* devl)
{
    if (!devl) {
        DEBUG("NULL given");
        return 0;
    }

    return devl->out_devices.size();
}

const char* cpd_audio_input_device_name(t_cpd_audio_devlist* devl, size_t n)
{
    if (!devl) {
        DEBUG("NULL given");
        return "";
    }

    if (n < devl->in_devices.size())
        return devl->in_devices[n].c_str();

    ERROR("invalid index: {}", n);
    return "";
}

const char* cpd_audio_output_device_name(t_cpd_audio_devlist* devl, size_t n)
{
    if (!devl) {
        DEBUG("NULL given");
        return "";
    }

    if (n < devl->out_devices.size())
        return devl->out_devices[n].c_str();

    ERROR("invalid index: {}", n);
    return "";
}

extern "C" int m_mainloop(void);
extern "C" void sys_exit(void);

static std::thread* dsp_thread = 0;
static std::mutex dsp_thread_mutex;

int cpd_dsp_thread_start()
{
    std::lock_guard<std::mutex> dsp_lock(dsp_thread_mutex);

    DEBUG("starting DSP thread mainloop...");

    if (dsp_thread != nullptr) {
        ERROR("DSP thread already started");
        return 0;
    }

    dsp_thread = new std::thread(m_mainloop);
    return 1;
}

int cpd_dsp_thread_stop()
{
    std::lock_guard<std::mutex> dsp_lock(dsp_thread_mutex);
    if (dsp_thread == nullptr) {
        ERROR("DSP is not started yet");
        return 0;
    }

    DEBUG("stopping DSP thread mainloop...");

    sys_exit();

    if (dsp_thread->joinable()) {
        dsp_thread->join();
        delete dsp_thread;
    }

    dsp_thread = nullptr;
    return 1;
}
