#include "catch.hpp"

#include "abstractserverprocess.h"
#include "canvas.h"
#include "pd_localserver.h"
#include "pd_object.h"

using namespace xpd;

TEST_CASE("PdObject", "[server]")
{
    PdLocalServer srv(ServerSettings("local"));
    ProcessPtr p = srv.createProcess();
    CanvasPtr c = p->createCanvas();

    SECTION("init")
    {
        REQUIRE(c->type() == OBJ_TYPE_CANVAS);

        auto o = std::make_shared<PdObject>(c.get(), "mtof", PdArguments(), 100, 200);
        REQUIRE(o->x() == 100);
        REQUIRE(o->y() == 200);

        REQUIRE(o->inletCount() == 1);
        REQUIRE(o->outletCount() == 1);

        o = std::make_shared<PdObject>(c.get(), "metro", PdArguments(), 10, 20);
        REQUIRE(o->x() == 10);
        REQUIRE(o->y() == 20);

        REQUIRE(o->inletCount() == 2);
        REQUIRE(o->outletCount() == 1);

        REQUIRE_FALSE(o->isRoot());
        REQUIRE_FALSE(o->hasChildren());
        REQUIRE(o->children().empty());
        REQUIRE(o->type() == OBJ_TYPE_SIMPLE_BOX);
    }

    SECTION("inlet count")
    {
        auto o = std::make_shared<PdObject>(c.get(), "metro");
        REQUIRE(o->inletCount() == 2);
        REQUIRE(o->outletCount() == 1);

        PdArguments args;
        args.parseString("f f f 123 s s");
        o = std::make_shared<PdObject>(c.get(), "pack", args);
        REQUIRE(o->inletCount() == 6);
        REQUIRE(o->outletCount() == 1);

        REQUIRE(o->arguments().getStringAt(0) == std::string("f"));
        REQUIRE(o->arguments().getStringAt(1) == std::string("f"));
        REQUIRE(o->arguments().getStringAt(2) == std::string("f"));
        REQUIRE(o->arguments().getFloatAt(3) == 123);
        REQUIRE(o->arguments().getStringAt(4) == std::string("s"));
        REQUIRE(o->arguments().getStringAt(5) == std::string("s"));
    }
}
