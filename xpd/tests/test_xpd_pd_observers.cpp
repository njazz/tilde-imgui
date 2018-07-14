#include "catch.hpp"

//#include "abstractserver.h"
//#include "abstractserverprocess.h"

#include "pd_consoleobserver.h"
#include "pd_objectobserver.h"

#include <algorithm>
#include <memory>
#include <numeric>
#include <string>

using namespace xpd;

extern const char* CATCHER_NAME;

class PdObjectObserverMock : public PdObjectObserver {
public:
    virtual void update() override { updateOk = true; };
    bool updateOk = false;
};

class PdConsoleObserverMock : public PdConsoleObserver {
public:
    static ConsoleObserverPtr pdConsoleObserver() { return PdConsoleObserver::_pdConsoleObserver; };
};

TEST_CASE("PdObservers", "[PdObservers]")
{
    PdObjectObserverMock pdo;

    SECTION("PdObjectObserver")
    {
        PdArguments cl;

        pdo.setData(cl);
        // TODO
        // REQUIRE(pdo.data() == cl);

        pdo.update();
        REQUIRE(pdo.updateOk);
    }

    SECTION("PdConsoleObserver")
    {
        //ConsoleObserver co;
        auto co_ptr = std::make_shared<ConsoleObserver>();

        co_ptr->setText("test");
        REQUIRE(co_ptr->text() == "test");

        PdConsoleObserver::setPdConsoleObserver(ConsoleObserverPtr(co_ptr));
//        REQUIRE(PdConsoleObserverMock::pdConsoleObserver().get() == co_ptr);

        PdConsoleObserver::hookFunction("hookFunction");
        REQUIRE(co_ptr->text() == "hookFunction");
    }
}
