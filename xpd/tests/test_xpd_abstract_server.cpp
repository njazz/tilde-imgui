#include "catch.hpp"

#include "abstractserver.h"
#include "abstractserverprocess.h"

#include <algorithm>
#include <memory>
#include <numeric>
#include <string>

using namespace xpd;

class AbstractServerMock : public AbstractServer {

public:
    AbstractServerMock(const ServerSettings& s)
        : AbstractServer(s){};

    virtual ProcessPtr createProcess() override { return 0; };
};

extern const char* CATCHER_NAME;

TEST_CASE("AbstractServer", "[AbstractServer]")
{
    SECTION("serverSettings")
    {
        ServerSettings s1("testOne");
        ServerSettings s2("testOne");
        ServerSettings s3("testThree");

        REQUIRE(s1.name() == "testOne");

        REQUIRE(s1 == s2);
        REQUIRE(s1 != s3);
    }

    AbstractServerMock srv(ServerSettings("local"));

    SECTION("abstractServer")
    {
        ProcessPtr p = srv.createProcess();
        REQUIRE(p.get() == 0);

        REQUIRE(srv.name() == "local");
        REQUIRE(srv.settings() == ServerSettings("local"));

        srv.setSettings(ServerSettings("newLocal"));
        REQUIRE(srv.name() == "newLocal");
        REQUIRE(srv.settings() == ServerSettings("newLocal"));
    }
}
