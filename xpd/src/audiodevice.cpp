#include "audiodevice.h"

namespace xpd {

AudioDevice::AudioDevice(const std::string& name)
    : Device(name)
{
}

AudioDevice::~AudioDevice()
{
}

} // namespace xpd
