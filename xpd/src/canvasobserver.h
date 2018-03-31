#ifndef CANVASOBSERVER_H
#define CANVASOBSERVER_H

#include "observer.h"

namespace xpd {

/**
 * @brief The CanvasObserver class
 * @details Observer base class for abstract Canvas class
 */
class CanvasObserver : public Observer {
public:
    CanvasObserver();

    /// @brief Called when inlet is added
    virtual void inletAdded();
    /// @brief Called when inlet is removed
    virtual void inletRemoved();

    /// @brief Called when outlet is added
    virtual void outletAdded();
    /// @brief Called when outlet is added
    virtual void outletRemoved();
};

} // namespace xpd

#endif // CANVASOBSERVER_H
