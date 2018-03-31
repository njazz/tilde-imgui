#include "catch.hpp"

//#include "abstractserver.h"
#include "abstractserverprocess.h"

#include <algorithm>
#include <memory>
#include <numeric>
#include <string>

using namespace xpd;

extern const char* CATCHER_NAME;

class AbstractServerProcessMock : public AbstractServerProcess {
public:
    AbstractServerProcessMock(const AbstractServer* parent, const ServerProcessSettings& s)
        : AbstractServerProcess(parent, s){};

    virtual void dspSwitch(bool value) override{};
    virtual CanvasPtr createCanvas() override { return CanvasPtr(0); }

    virtual bool loadLibrary(const std::string& libraryName) override { return true; };
    virtual bool loadExternal(const std::string& externalName) override { return true; };

    virtual void addSearchPath(const std::string &path) override {};

    virtual void sendMessage(const std::string& object, const std::string& text) override{};

};

TEST_CASE("AbstractServerProcess", "[AbstractServerProcess]")
{
    ServerProcessSettings s;
    AbstractServerProcessMock srv(0, s);

    SECTION("abstractServerProcess")
    {

        //        ServerProcessSettings ts = srv.settings();
        //        REQUIRE(ts == s);

        //        ServerProcessSettings s2;
        //        srv.setSettings(s2);
        //        ts = srv.settings();
        //        REQUIRE(ts == s2);

        //
        REQUIRE(srv.loadLibrary(""));
        REQUIRE(srv.loadExternal(""));

        REQUIRE(srv.createCanvas().get() == 0);
    }
}
