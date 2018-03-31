#include "catch.hpp"

//#include "abstractserver.h"
//#include "abstractserverprocess.h"

//#include "pd_objectobserver.h"
//#include "pd_consoleobserver.h"

#include "pd_arguments.h"

#include <algorithm>
#include <memory>
#include <numeric>
#include <string>

#include "pd_localserver.h"

using namespace xpd;

extern const char* CATCHER_NAME;

TEST_CASE("PdArguments", "[PdArguments]")
{
    PdArguments a1;

    REQUIRE(a1.args().size() == 0);

    PdArguments a2(0.33);

    REQUIRE(a2.args().size() == 1);
    REQUIRE(a2.args().at(0).is<float>());
    REQUIRE(a2.args().at(0).get<float>() == 0.33f);

    // !!!
    // should work without Pd initialized
    PdLocalServer srv(ServerSettings("local"));
    srv.createProcess();

    PdArguments a3(std::string("string"));

    REQUIRE(a3.args().size() == 1);
    REQUIRE(a3.args().at(0).is<std::string>());
    REQUIRE(a3.args().at(0).get<std::string>() == "string");

    PdArguments a4;
    a4.parseString("1 symbol 3.1415");

    REQUIRE(a4.args().size() == 3);
    REQUIRE(a4.args().at(0).is<float>());
    REQUIRE(a4.args().at(0).get<float>() == 1);

    REQUIRE(a4.args().at(1).is<std::string>());
    REQUIRE(a4.args().at(1).get<std::string>() == "symbol");

    REQUIRE(a4.args().at(2).is<float>());
    REQUIRE(a4.args().at(2).get<float>() == 3.1415f);
}
