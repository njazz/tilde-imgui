#include "device.h"

using namespace xpd;

Device::Device(const std::string& name)
    : name_(name)
{
}

Device::~Device()
{
}

const std::string& Device::name() const
{
    return name_;
}
