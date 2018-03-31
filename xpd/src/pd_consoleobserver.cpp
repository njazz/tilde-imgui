#include "pd_consoleobserver.h"

namespace xpd {

ConsoleObserverPtr PdConsoleObserver::_pdConsoleObserver = 0;

void PdConsoleObserver::hookFunction(const char* str)
{
    if (!str) return;

    if (_pdConsoleObserver) {
        //cout << "print hook: " << str << endl;
        _pdConsoleObserver->setText(str);
        _pdConsoleObserver->update();
    }
}

void PdConsoleObserver::setPdConsoleObserver(ConsoleObserverPtr o)
{
    _pdConsoleObserver = o;
}

} // namespace xpd
