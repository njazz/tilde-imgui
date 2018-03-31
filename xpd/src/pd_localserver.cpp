#include "pd_localserver.h"
#include "logger.h"
#include "pd_localprocess.h"

namespace xpd {

PdLocalServer::PdLocalServer(const ServerSettings& s)
    : AbstractServer(s)
{
}

PdLocalServer::~PdLocalServer()
{
}

ProcessPtr PdLocalServer::createProcess()
{
    if (process_list_.size() > 0)
        return process_list_.front();

    ProcessPtr ptr;

    try {
        ServerProcessSettings s;
        ptr = std::make_shared<PdLocalProcess>(this, s);

        if (!ptr)
            return ptr;

    } catch (std::exception& e) {
        log()->critical("LocalPdProcess crashed: {}", e.what());
        return ProcessPtr();
    }

    process_list_.push_back(ptr);
    return process_list_.front();
}

} // namespace xpd
