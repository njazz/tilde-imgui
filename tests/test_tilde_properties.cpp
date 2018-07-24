#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Properties/Property.h"
#include "Properties/PropertyList.h"
#include "json.hpp"

#include "PdStringConverter.h"

#include <initializer_list>
#include <tuple>

#include <string>
#include <vector>

TEST_CASE("properties: basic", "[tilde~ PureData IDE]")
{
    SECTION("JSON/PdString - error input")
    {
        ///\todo all types

        auto p = new PropertyT<float>();

        json j = json::array();

        p->fromJSON(j);
        p->fromJSONString("@#$%^");
        p->fromJSONString("{}");

        p->fromPdString("@#$%^");

        REQUIRE(true);
    }

    ///\todo test all T* properties fromJSON/fromPdString with nullptr value
    ///
    SECTION("float")
    {
        auto p = new PropertyT<float>();

        p->setDefaultValue(42.0f);
        REQUIRE(p->get() == 42.0f);
        REQUIRE(p->isDefault());

        p->set(0.33);
        REQUIRE(p->get() == 0.33f);
        REQUIRE(!p->isDefault());
        REQUIRE(p->is<float>());
        REQUIRE(!p->is<int>());

        REQUIRE(p->asPdString() == std::to_string(0.33f));

        // JSON
        auto p2 = new PropertyT<float>();

        p2->fromJSON(p->toJSON());
        REQUIRE(p->get() == p2->get());

        p2->set(0);
        p2->fromPdString(p->asPdString());
        REQUIRE(p->get() == p2->get());

        delete p2;
        delete p;
    }

    SECTION("int")
    {
        auto p = new PropertyT<int>();

        p->setDefaultValue(42);
        REQUIRE(p->get() == 42);
        REQUIRE(p->isDefault());

        p->set(33);
        REQUIRE(p->get() == 33);
        REQUIRE(!p->isDefault());

        REQUIRE(p->is<int>());
        REQUIRE(!p->is<float>());

        REQUIRE(p->asPdString() == std::to_string(33));

        // JSON
        auto p2 = new PropertyT<int>();

        p2->fromJSON(p->toJSON());
        REQUIRE(p->get() == p2->get());

        p2->set(0);
        p2->fromPdString(p->asPdString());
        REQUIRE(p->get() == p2->get());

        delete p2;
        delete p;
    }

    SECTION("string")
    {
        auto p = new PropertyT<std::string>();

        p->setDefaultValue("fourty two");
        REQUIRE(p->get() == "fourty two");
        REQUIRE(p->isDefault());

        p->set("33");
        REQUIRE(p->get() == "33");
        REQUIRE(!p->isDefault());

        REQUIRE(p->is<std::string>());
        REQUIRE(!p->is<float>());

        REQUIRE(p->asPdString() == "33");

        // JSON
        auto p2 = new PropertyT<std::string>();

        p2->fromJSON(p->toJSON());
        REQUIRE(p->get() == p2->get());

        p2->set("");
        p2->fromPdString(p->asPdString());
        REQUIRE(p->get() == p2->get());

        delete p2;
        delete p;
    }

    SECTION("bool")
    {
        auto p = new PropertyT<bool>();

        p->setDefaultValue(true);
        REQUIRE(p->get() == true);
        REQUIRE(p->isDefault());

        p->set(false);
        REQUIRE(p->get() == false);
        REQUIRE(!p->isDefault());

        REQUIRE(p->is<bool>());
        REQUIRE(!p->is<float>());

        REQUIRE(p->asPdString() == "0");

        // JSON
        auto p2 = new PropertyT<bool>();
        p->set(true);

        p2->fromJSON(p->toJSON());
        REQUIRE(p->get() == p2->get());

        p2->set(false);
        p2->fromPdString(p->asPdString());
        REQUIRE(p->get() == p2->get());

        delete p2;
        delete p;
    }

    SECTION("vector-string")
    {
        auto p = new PropertyT<std::vector<std::string> >();

        p->setDefaultValue({ "fourty", "two" });
        REQUIRE(p->get().size() == 2);
        REQUIRE(p->isDefault());

        //        REQUIRE(p->get()[0] == "fourty");
        //        REQUIRE(p->get()[1] == "two");

        p->set({ "33" });
        REQUIRE(p->get().size() == 1); // == "33");
        REQUIRE(!p->isDefault());

        //      REQUIRE(p->get()[0] == "33");

        REQUIRE(p->is<std::vector<std::string> >());
        REQUIRE(!p->is<float>());

        REQUIRE(p->asPdString() == "33");

        // JSON
        auto p2 = new PropertyT<std::vector<std::string> >();

        p2->fromJSON(p->toJSON());
        REQUIRE(p->get() == p2->get());

        p2->set({});
        p2->fromPdString(p->asPdString());
        REQUIRE(p->get() == p2->get());

        delete p2;
        delete p;
    }

    SECTION("string-enum")
    {
        auto p = new PropertyT<StringEnum>();

        StringEnum s1 = StringEnum({ "one", "two" }, 1);

        p->setDefaultValue(s1);
        REQUIRE(p->get() == s1);
        REQUIRE(p->isDefault());

        StringEnum s2 = StringEnum({ "a", "b", "c" }, 2);
        p->set(s2);
        REQUIRE(p->get() == s2);
        REQUIRE(!p->isDefault());

        REQUIRE(p->is<StringEnum>());
        REQUIRE(!p->is<float>());

        REQUIRE(p->asPdString() == "2 a b c");

        // JSON
        auto p2 = new PropertyT<StringEnum>();

        p2->fromJSON(p->toJSON());
        REQUIRE(p->get() == p2->get());

        p2->set(StringEnum());
        p2->fromPdString(p->asPdString());
        REQUIRE(p->get() == p2->get());

        delete p2;
        delete p;
    }

    SECTION("color")
    {
        auto p = new PropertyT<Color>();

        p->setDefaultValue(Color(.1, .2, .3, .4));
        REQUIRE(p->get() == Color(.1, .2, .3, .4));

        p->set(Color(1, 1, 1, 1));
        REQUIRE(p->get() == Color(1, 1, 1, 1));

        REQUIRE(p->is<Color>());
        REQUIRE(!p->is<float>());

        REQUIRE(p->asPdString() == "1.000000 1.000000 1.000000 1.000000");

        // JSON
        auto p2 = new PropertyT<Color>();

        p2->fromJSON(p->toJSON());
        REQUIRE(p->get() == p2->get());

        p2->set(Color(0, 0, 0, 0));
        p2->fromPdString(p->asPdString());
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

        p2->fromPdString(p->asPdString());
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

        p2->fromPdString(p->asPdString());
        REQUIRE(*p->get() == *p2->get());

        delete p2;
        delete p;
        delete i_;
        delete i2;
    }

    SECTION("bool*")
    {
        bool* i_ = new bool;
        *i_ = true;
        auto p = new PropertyT<bool*>(&i_);

        REQUIRE(*p->get() == true);

        *i_ = false;

        REQUIRE(*p->get() == false);
        REQUIRE(p->is<bool*>());
        REQUIRE(!p->is<float>());

        *i_ = true;
        REQUIRE(p->asPdString() == "1");

        // JSON
        bool* i2 = new bool;
        *i2 = false;
        auto p2 = new PropertyT<bool*>(&i2);

        p2->fromJSON(p->toJSON());
        REQUIRE(*p->get() == *p2->get());

        p2->fromPdString(p->asPdString());
        REQUIRE(*p->get() == *p2->get());

        delete p2;
        delete p;
        delete i_;
        delete i2;
    }

    SECTION("string*")
    {
        std::string s1 = "fourty two";
std::string s2 = "s2";

        auto p = new PropertyT<std::string*>();

        p->setDefaultValue(&s1);
        REQUIRE(*p->get() == "fourty two");
        REQUIRE(p->isDefault());

        //p->set("33");
        s1 = "33";
        REQUIRE(*p->get() == "33");

        REQUIRE(p->is<std::string*>());
        REQUIRE(!p->is<float>());

        REQUIRE(p->asPdString() == "33");

        // JSON
        auto p2 = new PropertyT<std::string*>();
        p2->set(&s2);

        p2->fromJSON(p->toJSON());
        REQUIRE(*p->get() == *p2->get());



        p2->fromPdString(p->asPdString());
        REQUIRE(*p->get() == *p2->get());

        delete p2;
        delete p;
    }

    SECTION("vector-float*")
    {
        float x = 0;
        float y = 0;

        float x2 = 0;
        float y2 = 0;

        auto vec = { &x, &y };
        auto p = new PropertyT<std::vector<float*> >();

        p->setDefaultValue(vec);
        p->set(vec);

        x = 33;
        y = 42;

        REQUIRE(p->get().size() == 2);

        REQUIRE(p->is<std::vector<float*> >());
        REQUIRE(!p->is<float>());

        // todo
        REQUIRE(p->asPdString() == "33.000000 42.000000");

        auto p2 = new PropertyT<std::vector<float*> >();
        p2->set({ &x2, &y2 });

        p2->fromJSON(p->toJSON());
        REQUIRE(*p->get()[0] == *p2->get()[0]);

        delete p2;
        delete p;
    }

    // stub
//    SECTION("vector-string*")
//    {
//        std::string x = "a";
//        std::string y = "b";

//        std::string x2 = "c";
//        std::string y2 = "d";

//        auto vec = { &x, &y };
//        auto p = new PropertyT<std::vector<std::string*> >();

//        p->setDefaultValue(vec);
//        p->set(vec);

//        x = "33";
//        y = "42";

//        REQUIRE(p->get().size() == 2);

//        REQUIRE(p->is<std::vector<float*> >());
//        REQUIRE(!p->is<float>());

//        // todo
//        REQUIRE(p->asPdString() == "33 42");

//        auto p2 = new PropertyT<std::vector<std::string*> >();
//        p2->set({ &x2, &y2 });

//        p2->fromJSON(p->toJSON());
//        REQUIRE(*p->get()[0] == *p2->get()[0]);

//        delete p2;
//        delete p;
//    }
}

TEST_CASE("propertylist", "[tilde~ PureData IDE]")
{

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

    SECTION("basic")
    {
        TestSpecificPropertyList pl;

        pl.set("Property-One", 11);
        pl.set("Property-Two", std::string("fourty-two"));
        pl.set("Property-Three", 11.0f);

        REQUIRE(pl.get("Property-One")->typed<int>()->get() == 11);
        REQUIRE(pl.get("Property-Two")->typed<std::string>()->get()[0] == 'f'); //todo
        REQUIRE(pl.get("Property-Three")->typed<float>()->get() == 11.0f);
    }



    SECTION("JSON")
    {
        TestSpecificPropertyList pl;

        TestSpecificPropertyList pl2;
        //pl2.set("Property-Three", 43.0f);
        pl2.set("Property-One", 0);

        // TODO: set non-existing property

        printf("JSON p1: %s\n", pl.toJSONString().c_str());
        printf("JSON p2: %s\n", pl2.toJSONString().c_str());

        REQUIRE(pl2.toJSONString() != pl.toJSONString());

        pl2.fromJSON(pl.toJSON());
        REQUIRE(pl2.toJSONString() == pl.toJSONString());

        pl2.set("Property-One", 0);

        pl2.fromJSONString(pl.toJSONString());
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
        pl2.extractFromPdFileString(pl.asPdFileString());
        REQUIRE(pl2.asPdFileString() == pl.asPdFileString());
    }

    SECTION("Groups")
    {
        TestSpecificPropertyList pl;

        REQUIRE(pl.groupNames().size() == 2);

        REQUIRE(pl.fromGroup("Group A")->size() == 2);

        REQUIRE(pl.fromGroup("Nothing") == 0);

        REQUIRE(pl.namesInGroup(pl.fromGroup("Group A")).size() == 2);
    }

    SECTION("Utilities")
    {
        // basic
        REQUIRE(splitStringByToken("1 2 3", " ").size() == 3);
        REQUIRE(splitStringByToken("@property value @p2 @p3 value", " @").size() == 3);

        REQUIRE(strncmp(joinStringWithToken({ "A", "B", "C" }, " ").c_str(), "A B C", 5) == 0);

        std::string str_ = "@property name 1 {} () []";

        auto split = splitStringByToken(str_, " ");
        auto join = joinStringWithToken(split, " ");
        //REQUIRE(!strncmp(str_.c_str(),join.c_str(),str_.length()));
        printf("%s || %s\n", str_.c_str(), join.c_str());

        auto esc = PdStringConverter::escapeString(str_);
        auto u_esc = PdStringConverter::unescapeString(esc);

        REQUIRE(!strncmp(esc.c_str(), u_esc.c_str(), esc.length()));
    }
}
