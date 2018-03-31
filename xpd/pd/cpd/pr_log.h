#ifndef PR_LOG_H
#define PR_LOG_H

#include "cpd_def.h"
#include "spdlog/spdlog.h"

std::shared_ptr<spdlog::logger>& console();

#define DEBUG(fmt, ...) console()->debug("{}: " fmt, __FUNCTION_NAME__, ##__VA_ARGS__)
#define WARNING(fmt, ...) console()->warn("{}: " fmt, __FUNCTION_NAME__, ##__VA_ARGS__)
#define ERROR(fmt, ...) console()->error("{}: " fmt, __FUNCTION_NAME__, ##__VA_ARGS__)
#define TRACE(fmt, ...) console()->trace("{}: " fmt, __FUNCTION_NAME__, ##__VA_ARGS__)
#define INFO(fmt, ...) console()->info("{}: " fmt, __FUNCTION_NAME__, ##__VA_ARGS__)

#endif // PR_LOG_H
