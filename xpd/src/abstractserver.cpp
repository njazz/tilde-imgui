#include "abstractserver.h"

namespace xpd {

AbstractServer::AbstractServer(const ServerSettings& s)
    : settings_(s)
{
}

AbstractServer::~AbstractServer()
{
}

const ServerSettings& AbstractServer::settings() const
{
    return settings_;
}

void AbstractServer::setSettings(const ServerSettings& s)
{
    settings_ = s;
}

const ProcessList& AbstractServer::processList() const
{
    return process_list_;
}

const std::string& AbstractServer::name() const
{
    return settings_.name();
}

const std::string& ServerSettings::name() const
{
    return name_;
}

bool ServerSettings::operator==(const ServerSettings& s) const
{
    return name_ == s.name_;
}

bool ServerSettings::operator!=(const ServerSettings& s) const
{
    return !operator==(s);
}

} // namespace xpd
