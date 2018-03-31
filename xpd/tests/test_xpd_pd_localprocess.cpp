#include "catch.hpp"

#include "pd_localprocess.h"

#include <algorithm>
#include <memory>
#include <numeric>
#include <string>

using namespace xpd;

extern const char* CATCHER_NAME;

TEST_CASE("PdLocalProcess", "[PdLocalProcess]")
{
    ServerProcessSettings s;
    PdLocalProcess srv(0, s);

    SECTION("PdLocalProcess")
    {

    }
}
