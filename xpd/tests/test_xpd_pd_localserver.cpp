#include "catch.hpp"

#include "abstractserverprocess.h"
#include "pd_localserver.h"

using namespace xpd;

TEST_CASE("localserver", "[server]")
{
    SECTION("init")
    {
        ServerSettings s("local pd");
        PdLocalServer srv(s);

        REQUIRE(srv.name() == "local pd");
        REQUIRE(srv.processList().empty());

        ServerSettings s1("other pd");
        srv.setSettings(s1);
        REQUIRE(srv.settings() == s1);
        REQUIRE(srv.settings() != s);

        REQUIRE(srv.name() == "other pd");
    }

    SECTION("create")
    {
        PdLocalServer srv(ServerSettings("local"));

        ProcessPtr p0 = srv.createProcess();
        REQUIRE(p0);
        REQUIRE(srv.processList().size() == 1);

        ProcessPtr p1 = srv.createProcess();
        REQUIRE(p0);
        REQUIRE(p0 == p1);
        REQUIRE(srv.processList().size() == 1);

        REQUIRE(p1->parent() == p0->parent());
        REQUIRE(p1->parent() == &srv);

        // create new canvas
        REQUIRE(p0->canvasCount() == 0);
        CanvasPtr cnv0 = p0->createCanvas();

        REQUIRE(cnv0);
        REQUIRE(p0->canvasCount() == 1);
        REQUIRE(p0->canvasList().size() == 1);
    }

    SECTION("c2")
    {
        PdLocalServer srv(ServerSettings("local"));

        {
            ProcessPtr p = srv.createProcess();
            CanvasPtr cnv = p->createCanvas();
            REQUIRE(p->canvasCount() == 1);
            REQUIRE(!p->deleteCanvas(CanvasPtr()));
            REQUIRE(p->canvasCount() == 1);
            REQUIRE(p->deleteCanvas(cnv));
            REQUIRE(p->canvasCount() == 0);
        }

        {
            ProcessPtr p = srv.createProcess();
            CanvasPtr cnv = p->createCanvas();
            REQUIRE(p->canvasCount() == 1);
        }
    }

    SECTION("obj")
    {
        PdLocalServer srv(ServerSettings("local"));
        ProcessPtr p = srv.createProcess();
        CanvasPtr cnv = p->createCanvas();

        REQUIRE(cnv->createObject("unknown", 100, 200) == 0);
        ObjectId id = cnv->createObject("mtof", 100, 200);
        REQUIRE(id != 0);

        REQUIRE(cnv->hasChildren());
        REQUIRE(cnv->childrenCount() == 1);
    }

    SECTION("connect")
    {
        PdLocalServer srv(ServerSettings("local"));
        ProcessPtr p = srv.createProcess();
        CanvasPtr cnv = p->createCanvas();

        ObjectId id0 = cnv->createObject("mtof", 100, 200);
        REQUIRE(id0 != 0);

        ObjectId id1 = cnv->createObject("print", 100, 200);
        REQUIRE(id1 != 0);

        REQUIRE(cnv->connect(id0, 0, id1, 0));

        cnv->sendFloat(id0, 60);
    }
}
