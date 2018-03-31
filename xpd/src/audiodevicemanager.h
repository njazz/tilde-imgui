#ifndef AUDIODEVICEMANAGER_H
#define AUDIODEVICEMANAGER_H

#include <memory>
#include <vector>

#include "audiodevice.h"

namespace xpd {

typedef std::unique_ptr<AudioDevice> AudioDevicePtr;
typedef std::vector<AudioDevicePtr> AudioDeviceList;

/**
 * @brief The AudioDeviceManager class
 */
class AudioDeviceManager {
    AudioDeviceList dev_list_;

public:
    AudioDeviceManager();
};

} // namespace xpd

#endif // AUDIODEVICEMANAGER_H
