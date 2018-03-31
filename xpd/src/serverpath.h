#ifndef SERVERPATH_H
#define SERVERPATH_H

#include <string>
#include <vector>

namespace xpd {

/**
 * @brief The ServerPath class
 */
class ServerPath {
    std::vector<std::string> paths_;

public:
    ServerPath();
};

} // namespace xpd

#endif // SERVERPATH_H
