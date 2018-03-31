#ifndef MIDIDEVICEMANAGER_H
#define MIDIDEVICEMANAGER_H

#include <memory>
#include <vector>

#include "mididevice.h"

namespace xpd {

typedef std::unique_ptr<MIDIDevice> MIDIDevicePtr;
typedef std::vector<MIDIDevicePtr> MIDIDeviceList;

/**
 * @brief The MIDIDeviceManager class
 */
class MIDIDeviceManager {
    MIDIDeviceList dev_list_;

public:
    MIDIDeviceManager();
};

} // namespace xpd

#endif // MIDIDEVICEMANAGER_H
