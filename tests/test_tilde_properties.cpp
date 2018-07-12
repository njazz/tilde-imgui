#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Properties/Property.h"
#include "Properties/PropertyList.h"

TEST_CASE("properties: basic", "[tilde~ PureData IDE]")
{
    SECTION("float")
    {
        auto p = new PropertyT<float>();

        p->setDefaultValue(42.0f);
        REQUIRE(p->get() == 42.0f);

        p->set(0.33);
        REQUIRE(p->get() == 0.33f);
        REQUIRE(p->is<float>());
        REQUIRE(!p->is<int>());

        REQUIRE(p->asPdString() == std::to_string(0.33f));

        delete p;
    }

    SECTION("int")
    {
        auto p = new PropertyT<int>();

        p->setDefaultValue(42);
        REQUIRE(p->get() == 42);

        p->set(33);
        REQUIRE(p->get() == 33);
        REQUIRE(p->is<int>());
        REQUIRE(!p->is<float>());

        REQUIRE(p->asPdString() == std::to_string(33));

        delete p;
    }

    SECTION("string")
    {
        auto p = new PropertyT<std::string>();

        p->setDefaultValue("fourty two");
        REQUIRE(p->get() == "fourty two");

        p->set("33");
        REQUIRE(p->get() == "33");
        REQUIRE(p->is<std::string>());
        REQUIRE(!p->is<float>());

        REQUIRE(p->asPdString() == "33");

        delete p;
    }
}

TEST_CASE("properties: pointers", "[tilde~ PureData IDE]")
{
    SECTION("float*")
    {
        float* f_ = new float;
        *f_ = 100;
        auto p = new PropertyT<float*>(&f_);

        REQUIRE(*p->get() == 100.0f);

        *f_ = 0.33;

        REQUIRE(*p->get() == 0.33f);
        REQUIRE(p->is<float*>());
        REQUIRE(!p->is<float>());

        REQUIRE(p->asPdString() == std::to_string(0.33f));

        delete p;
        delete f_;
    }

    SECTION("int*")
    {
        int* i_ = new int;
        *i_ = 100;
        auto p = new PropertyT<int*>(&i_);

        REQUIRE(*p->get() == 100);

        *i_ = 33;

        REQUIRE(*p->get() == 33);
        REQUIRE(p->is<int*>());
        REQUIRE(!p->is<float>());

        REQUIRE(p->asPdString() == std::to_string(33));

        delete p;
        delete i_;
    }
}

TEST_CASE("properties: list", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {

    }
}
