#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include "abstractserver.h"

namespace xpd {

/**
 * @brief The PdLocalServer class
 * @details See AbctractServer base class
 */
class PdLocalServer : public AbstractServer {
public:
    PdLocalServer(const ServerSettings& s);
    ~PdLocalServer();

    /// @brief Create new Pd process
    virtual ProcessPtr createProcess() override;
};

} // namespace xpd

#endif // LOCALSERVER_H
