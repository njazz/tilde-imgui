#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Properties/Property.h"
#include "Properties/PropertyList.h"
#include "json.hpp"

#include "PdStringConverter.h"

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

        // JSON
        auto p2 = new PropertyT<float>();

        p2->fromJSON(p->toJSON());
        REQUIRE(p->get() == p2->get());

        delete p2;
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

        // JSON
        auto p2 = new PropertyT<int>();

        p2->fromJSON(p->toJSON());
        REQUIRE(p->get() == p2->get());

        delete p2;
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

        // JSON
        auto p2 = new PropertyT<std::string>();

        p2->fromJSON(p->toJSON());
        REQUIRE(p->get() == p2->get());

        delete p2;
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

        // JSON
        float* f2 = new float;
        *f2 = 50;
        auto p2 = new PropertyT<float*>(&f2);

        p2->fromJSON(p->toJSON());
        REQUIRE(*p->get() == *p2->get());

        delete p2;
        delete p;
        delete f_;
        delete f2;
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

        // JSON
        int* i2 = new int;
        *i2 = 50;
        auto p2 = new PropertyT<int*>(&i2);

        p2->fromJSON(p->toJSON());
        REQUIRE(*p->get() == *p2->get());

        delete p2;
        delete p;
        delete i_;
        delete i2;
    }
}

TEST_CASE("propertylist", "[tilde~ PureData IDE]")
{
    SECTION("basic")
    {
        PropertyList pl;
    }

    class TestSpecificPropertyList : public PropertyList {
    public:
        TestSpecificPropertyList()
            : PropertyList()
        {
            // TODO: properties with spaces in names
            create("Property-One", "Group A", "42", 42);
            create("Property-Two", "Group A", "42", std::string("eleven"));
            create("Property-Three", "Group B", "42", -1.f);
        }
    };

    SECTION("JSON")
    {
        TestSpecificPropertyList pl;

        TestSpecificPropertyList pl2;
        pl2.set("Property-One", 0);

        // TODO: set non-existing property

        printf("JSON p1: %s\n", pl.toJSONString().c_str());
        printf("JSON p2: %s\n", pl2.toJSONString().c_str());

        REQUIRE(pl2.toJSONString() != pl.toJSONString());

        pl2.fromJSON(pl.toJSON());
        REQUIRE(pl2.toJSONString() == pl.toJSONString());
    }

    SECTION("Pd file string")
    {
        TestSpecificPropertyList pl;

        TestSpecificPropertyList pl2;
        pl2.set("Property-One", 0);

        printf("Pd string p1: %s\n", pl.asPdFileString().c_str());
        printf("Pd string p2: %s\n", pl2.asPdFileString().c_str());

        REQUIRE(pl2.asPdFileString() != pl.asPdFileString());

        // TODO:
        // TODO: properties with spaces in names
//        pl2.extractFromPdFileString(pl.asPdFileString());
//        REQUIRE(pl2.asPdFileString() == pl.asPdFileString());

    }

    SECTION ("Utilities")
    {
        // basic
        REQUIRE(splitStringByToken("1 2 3"," ").size() == 3);
        REQUIRE(splitStringByToken("@property value @p2 @p3 value"," @").size()==3);

        REQUIRE(strncmp(joinStringWithToken({"A","B","C"}," ").c_str(),"A B C",5)==0);

        std::string str_ = "@property name 1 {} () []";

        auto split = splitStringByToken(str_," ");
        auto join = joinStringWithToken(split," ");
        //REQUIRE(!strncmp(str_.c_str(),join.c_str(),str_.length()));
        printf("%s || %s\n",str_.c_str(),join.c_str());

        auto esc = PdStringConverter::escapeString(str_);
        auto u_esc = PdStringConverter::unescapeString(esc);

        REQUIRE(!strncmp(esc.c_str(),u_esc.c_str(),esc.length()));


    }
}
