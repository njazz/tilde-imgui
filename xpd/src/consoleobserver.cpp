#include "consoleobserver.h"

namespace xpd {

ConsoleObserver::ConsoleObserver()
{
}

void ConsoleObserver::setText(const std::string& text)
{
    text_ = text;
}

const std::string& ConsoleObserver::text() const
{
    return text_;
}

} // namespace xpd
