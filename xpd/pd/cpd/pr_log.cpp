#include "pr_log.h"

std::shared_ptr<spdlog::logger>& console()
{
    static std::shared_ptr<spdlog::logger> cons = spdlog::stdout_color_mt("cpd");
    return cons;
}
