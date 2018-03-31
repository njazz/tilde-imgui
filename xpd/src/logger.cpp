#include "logger.h"

namespace xpd {

std::shared_ptr<spdlog::logger> log()
{
    static auto console = spdlog::stdout_color_mt("xpd");
    return console;
}

} // namespace xpd
