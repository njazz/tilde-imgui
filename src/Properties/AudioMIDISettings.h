// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_AUDIOMIDI_H
#define CM_AUDIOMIDI_H

#include "PropertyList.h"
#include "json.hpp"

#include "cpd/cpd.h"
#include "pd_localprocess.h"
#include "pd_localserver.h"

// to be moved to xpd:
//class xpd_Audio {
//    t_cpd_audio_devlist* devlist_;

//public:
//    xpd_Audio()
//    {
//        cpd_audio_devlist_new();
//    }

//    ~xpd_Audio()
//    {
//        cpd_audio_devlist_free(devlist_);
//    }

//    int inputDeviceCount()
//    {
//        return cpd_audio_input_devices_num(devlist_);
//    };

//    int outputDeviceCount()
//    {
//        return cpd_audio_output_devices_num(devlist_);
//    };

//    std::vector<std::string> inputDevices()
//    {
//        std::vector<std::string> ret;
//        for (int i=0;i<inputDeviceCount();i++)
//        {
//            ret.push_back(cpd_audio_input_device_name(devlist_,i));
//        }

//        return ret;
//    }

//    std::vector<std::string> outputDevices()
//    {
//        std::vector<std::string> ret;
//        for (int i=0;i<outputDeviceCount();i++)
//        {
//            ret.push_back(cpd_audio_output_device_name(devlist_,i));
//        }

//        return ret;
//    }
//};

class AudioMIDISettings : public PropertyList {
    xpd::ProcessPtr pdProcess = 0;

public:
    AudioMIDISettings(xpd::ProcessPtr p);

    void loadFromJSONFile(){};
    void saveToJSONFile(){};
};

#endif // CM_PREFERENCES_H
