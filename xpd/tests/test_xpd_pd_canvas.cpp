#include "catch.hpp"

#include "abstractserver.h"
#include "abstractserverprocess.h"
#include "pd_canvas.h"
#include "pd_catcher.h"
#include "pd_localserver.h"

#include <algorithm>
#include <string>

using namespace xpd;

extern const char* CATCHER_NAME;

template <class T, class V>
static bool contains(const T& cont, const V& val)
{
    return std::find(std::begin(cont), std::end(cont), val) != std::end(cont);
}

TEST_CASE("PdCanvas", "[PdCanvas]")
{
    PdLocalServer srv(ServerSettings("local"));
    ProcessPtr p = srv.createProcess();
    CanvasPtr c = p->createCanvas();

    SECTION("init")
    {
        REQUIRE(c->type() == OBJ_TYPE_CANVAS);
        REQUIRE(c->inletCount() == 0);
        REQUIRE(c->outletCount() == 0);
    }

    SECTION("create array")
    {
        auto id0 = c->createArray("array1", 100);
        REQUIRE(id0 > 0);
        REQUIRE(c->childrenCount() == 1);
        REQUIRE(c->isRoot());
        REQUIRE(c->children().contains(id0));
        REQUIRE(c->children().findObjectIndex(id0) == 0);

        auto id1 = c->createObject("mtof", 0, 0);
        REQUIRE(c->childrenCount() == 2);
        REQUIRE(id0 < id1);
        REQUIRE(c->children().findObjectIndex(id0) == 0);
        REQUIRE(c->children().findObjectIndex(id1) == 1);

        // invalid index
        REQUIRE(c->children().findObjectIndex(-1000) == -1);
        c->removeAllChildren();
        REQUIRE(c->childrenCount() == 0);
        REQUIRE_FALSE(c->hasChildren());
    }

    SECTION("append remove")
    {
        auto sz = c->childrenCount();
        auto id0 = c->createObject("f", 0, 0);
        REQUIRE(c->childrenCount() == sz + 1);

        // invalid ID
        REQUIRE_FALSE(c->deleteObject(id0 + 1000));
        REQUIRE(c->childrenCount() == sz + 1);

        // remove
        REQUIRE(c->deleteObject(id0));
        REQUIRE(c->childrenCount() == sz);

        c->removeAllChildren();
        REQUIRE_FALSE(c->hasChildren());
    }

    SECTION("loadbang")
    {
        c->removeAllChildren();
        auto lb = c->createObject("loadbang", 0, 0);
        PdCatcher ct(c.get());
        REQUIRE(c->connect(lb, 0, ct.id(), 0));

        REQUIRE(ct.isEmpty());
        c->loadbang();
        REQUIRE(ct.isLastBang());
        REQUIRE_FALSE(ct.isLastFloat(123));
        ct.clear();
    }

    SECTION("subpatch")
    {
        c->removeAllChildren();
        auto sp_id = c->createObject("pd test", 0, 0);
        REQUIRE(sp_id > 0);
        REQUIRE(c->childrenCount() == 1);
        auto obj = c->children().findObject(sp_id);
        REQUIRE(obj);
        REQUIRE(c->children().findObjectIndex(sp_id) == 0);

        REQUIRE(obj->type() == OBJ_TYPE_CANVAS);       
        Canvas* subpatch = (Canvas*)obj->asCanvas();
        //PdCanvas* subpatch = ((PdObject*)obj)->asPdCanvas();
        REQUIRE(subpatch);
        REQUIRE(subpatch->inletCount() == 0);
        REQUIRE(subpatch->outletCount() == 0);

        auto inl_id = subpatch->createObject("inlet", 0, 0);
        auto otl_id = subpatch->createObject("outlet", 0, 0);

        REQUIRE(inl_id > sp_id);
        REQUIRE(otl_id > inl_id);

        REQUIRE(obj->childrenCount() == 2);
        REQUIRE(subpatch->childrenCount() == 2);

        REQUIRE(obj->inletCount() == 1);
        REQUIRE(obj->inlets().size() == 1);
        REQUIRE(obj->inlets()[0].type() == XLET_MESSAGE);

        REQUIRE(obj->outletCount() == 1);
        REQUIRE(obj->outlets().size() == 1);
        REQUIRE(obj->outlets()[0].type() == XLET_MESSAGE);

        auto inl2_id = subpatch->createObject("inlet~", 100, 0);
        auto otl2_id = subpatch->createObject("outlet~", 100, 0);

        REQUIRE(obj->inletCount() == 2);
        REQUIRE(obj->inlets().size() == 2);
        REQUIRE(obj->inlets()[0].type() == XLET_MESSAGE);
        REQUIRE(obj->inlets()[1].type() == XLET_SIGNAL);

        REQUIRE(obj->outletCount() == 2);
        REQUIRE(obj->outlets().size() == 2);
        REQUIRE(obj->outlets()[0].type() == XLET_MESSAGE);
        REQUIRE(obj->outlets()[1].type() == XLET_SIGNAL);

        // testing X-position
        auto inl3_id = subpatch->createObject("inlet", 50, 0);
        auto otl3_id = subpatch->createObject("outlet", 50, 0);

        REQUIRE(obj->inletCount() == 3);
        REQUIRE(obj->inlets()[0].type() == XLET_MESSAGE);
        REQUIRE(obj->inlets()[1].type() == XLET_MESSAGE);
        REQUIRE(obj->inlets()[2].type() == XLET_SIGNAL);

        REQUIRE(obj->outletCount() == 3);
        REQUIRE(obj->outlets()[0].type() == XLET_MESSAGE);
        REQUIRE(obj->outlets()[1].type() == XLET_MESSAGE);
        REQUIRE(obj->outlets()[2].type() == XLET_SIGNAL);
    }

    SECTION("list available objects")
    {
        auto lst = c->availableObjects();
        REQUIRE(lst.size() > 0);
        REQUIRE(contains(lst, "pd"));
        REQUIRE(contains(lst, "soundfiler"));
        REQUIRE(contains(lst, "&&"));
        REQUIRE(contains(lst, "f"));
        REQUIRE(contains(lst, "*~"));
        REQUIRE(contains(lst, "mtof"));
        REQUIRE(contains(lst, "list append"));
    }
}
