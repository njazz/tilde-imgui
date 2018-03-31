#include "libraryinfo.h"

namespace xpd {

LibraryInfo::LibraryInfo(const std::string& name)
    : name_(name)
{
}

const std::string& LibraryInfo::name() const
{
    return name_;
}

const std::string& LibraryInfo::version() const
{
    return version_;
}

} // namespace xpd
