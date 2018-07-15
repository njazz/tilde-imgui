#include "AudioMIDISettings.h"

AudioMIDISettings::AudioMIDISettings(xpd::ProcessPtr p)
    : PropertyList()
{

    pdProcess = p;

    create("Input Devices", "System", "0", pdProcess->audioInputDeviceList());
    create("Output Devices", "System", "0", pdProcess->audioOutputDeviceList());
}
