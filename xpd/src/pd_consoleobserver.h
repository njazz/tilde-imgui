#ifndef PD_CONSOLEOBSERVER_H
#define PD_CONSOLEOBSERVER_H

#include "consoleobserver.h"
#include <memory>

#include <string>

namespace xpd {

// todo: move this declaration
typedef std::shared_ptr<ConsoleObserver> ConsoleObserverPtr;

/**
 * @brief The PdConsoleObserver class
 */
class PdConsoleObserver : public ConsoleObserver {
protected:
    static ConsoleObserverPtr _pdConsoleObserver;

public:
    /// @brief Callback for PureData logging system
    static void hookFunction(const char* str);
    static void setPdConsoleObserver(ConsoleObserverPtr o);
};

} // namespace xpd

#endif // PD_CONSOLEOBSERVER_H
