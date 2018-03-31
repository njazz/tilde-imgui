#include "catch.hpp"

#include "abstractserverprocess.h"
#include "canvas.h"

using namespace xpd;

class TestObject : public Object {
public:
    TestObject(const std::string& name)
        : Object(0, name)
    {
        cnt++;
        id_ = cnt + 5000;
    }

    ~TestObject()
    {
        cnt--;
    }

    virtual size_t inletCount() const override { return 3; }
    virtual size_t outletCount() const override { return 1; }

    //virtual ObjectId createObject(const std::string &name, int x, int y) override {return 0;}

public:
    static int cnt;
};

int TestObject::cnt = 0;

TEST_CASE("ObjectList", "[server]")
{
    SECTION("init")
    {
        ObjectList lst;
        REQUIRE(lst.empty());
        REQUIRE(lst.size() == 0);
        REQUIRE(lst.connections().empty());
        REQUIRE(lst.size() == 0);
    }

    SECTION("append")
    {
        ObjectList lst;
        REQUIRE_FALSE(lst.append(0));

        REQUIRE(lst.size() == 0);

        REQUIRE(lst.append(new TestObject("test")));
        REQUIRE(lst.append(new TestObject("test")));

        REQUIRE(lst.size() == 2);

        auto o = new TestObject("test2");
        REQUIRE(lst.append(o));
        REQUIRE(lst.findObject(o->id()));
        REQUIRE(lst.contains(o->id()));

        // double insertion
        REQUIRE_FALSE(lst.append(o));
    }

    SECTION("connect")
    {
        ObjectList lst;
        auto o1 = new TestObject("object1");
        auto o2 = new TestObject("object1");

        lst.append(o1);
        lst.append(o2);

        REQUIRE(lst.contains(o1->id()));
        REQUIRE(lst.contains(o2->id()));

        REQUIRE(lst.connect(o1->id(), 0, o2->id(), 0));
        // double connection
        REQUIRE_FALSE(lst.connect(o1->id(), 0, o2->id(), 0));

        // other xlets
        REQUIRE(lst.connect(o1->id(), 0, o2->id(), 1));

        // invalid source
        REQUIRE_FALSE(lst.connect(101, 0, o2->id(), 0));
        // invalid dest
        REQUIRE_FALSE(lst.connect(o1->id(), 0, 201, 0));
        // invalid source inlet
        REQUIRE_FALSE(lst.connect(o1->id(), 1, o2->id(), 0));
        REQUIRE_FALSE(lst.connect(o1->id(), 2, o2->id(), 0));
        // invalid dest inlet
        REQUIRE_FALSE(lst.connect(o1->id(), 0, o2->id(), 3));
        REQUIRE_FALSE(lst.connect(o1->id(), 0, o2->id(), 4));

        REQUIRE(lst.isConnected(o1->id(), o2->id()));
        REQUIRE(lst.isConnected(o2->id(), o1->id()));
        REQUIRE_FALSE(lst.isConnected(o1->id(), o1->id()));
        REQUIRE_FALSE(lst.isConnected(o2->id(), o2->id()));

        // self connection
        REQUIRE_FALSE(lst.connect(o1->id(), 0, o1->id(), 0));
    }

    SECTION("disconnect")
    {
        ObjectList lst;
        auto o1 = new TestObject("object1");
        auto o2 = new TestObject("object1");

        lst.append(o1);
        lst.append(o2);
        REQUIRE(lst.connect(o1->id(), 0, o2->id(), 1));
        REQUIRE(lst.isConnected(o1->id(), o2->id()));

        REQUIRE(lst.disconnect(o1->id(), 0, o2->id(), 1));
        REQUIRE_FALSE(lst.isConnected(o1->id(), o2->id()));
        // second attempt
        REQUIRE_FALSE(lst.disconnect(o1->id(), 0, o2->id(), 1));
    }

    REQUIRE(TestObject::cnt == 0);
}
