#ifndef CONSOLEOBSERVER_H
#define CONSOLEOBSERVER_H

#include "observer.h"
#include <string>

namespace xpd {

/**
 * @brief The ConsoleObserver class
 * @details Base class for PdConsoleObserver
 */
class ConsoleObserver : public Observer {
    std::string text_;

public:
    ConsoleObserver();

    /// @brief Set text value
    void setText(const std::string& text);
    /// @brief Get text value
    const std::string& text() const;
};

} // namespace xpd

#endif // CONSOLEOBSERVER_H
