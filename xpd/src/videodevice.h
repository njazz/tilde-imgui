#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H

#include "device.h"

namespace xpd {

/**
 * @brief The VideoDevice class
 */
class VideoDevice : public Device {
public:
    VideoDevice(const std::string& name);
};

} // namespace xpd

#endif // VIDEODEVICE_H
