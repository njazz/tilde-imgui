#ifndef DEVICE_H
#define DEVICE_H

#include <string>

namespace xpd {

/**
 * @brief The Device class
 */
class Device {
protected:
    std::string name_;

public:
    Device(const std::string& name);
    virtual ~Device();

    /// @brief device name
    virtual const std::string& name() const;
};
}

#endif // DEVICE_H
