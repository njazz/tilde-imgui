#include "classinfo.h"

namespace xpd {

ClassInfo::ClassInfo(const std::string& name)
    : name_(name)
{
}

const std::string& ClassInfo::name() const
{
    return name_;
}

const std::string& ClassInfo::library() const
{
    return library_;
}

} // namespace xpd
