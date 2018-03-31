#ifndef LOGGER_H
#define LOGGER_H

#include "spdlog/spdlog.h"

namespace xpd {

std::shared_ptr<spdlog::logger> log();

} // namespace xpd

#endif // LOGGER_H
