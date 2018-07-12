// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_PROPERTY_H
#define CM_PROPERTY_H

#include <math.h>
#include <string>
#include <utility>
#include <vector>

#include <memory>

#include "IUAction.hpp"

#include <functional>

typedef enum {
    // empty
    ptNull,
    // basic
    ptBool,
    ptFloat,
    ptInt,
    ptSymbol,
    ptString,
    // arrays
    ptList,
    ptVector,
    ptVec2,
    ptColor,
    ptStringList,
    // specials
    ptPath, ///> file or directory
    ptPathList,
    ptEnum, ///> index and option list
    ptText ///< multiline text for comments, script

} UIPropertyType;

class Variant {
    int _intValue = 0;
    float _floatValue = 0;
    std::string _stringValue = "";

    int* _intPtr = 0; //&_intValue;
    float* _floatPtr = 0; //&_floatValue;
    std::string* _stringPtr = 0; //&_stringValue;

public:
    Variant(int v);
    Variant(long v);
    Variant(bool b);
    Variant(float f);
    Variant(double f);
    Variant(std::string s);

    template <typename T>
    void set(T val);

    template <typename T>
    T get();

    void bindInt(int* p)
    {
        _intPtr = p;
        _floatPtr = 0;
        _stringPtr = 0;
    }
    void bindFloat(float* p)
    {
        _floatPtr = p;
        _intPtr = 0;
        _stringPtr = 0;
    }
    void bindString(std::string* p)
    {
        _stringPtr = p;
        _intPtr = 0;
        _floatPtr = 0;
    }
};

//template<>
//std::string Variant::get()
//{
//    return _stringValue;
//}

//template<>
//float Variant::get()
//{
//    return _floatValue;
//}

//template<>
//int Variant::get()
//{
//    return _intValue;
//}

class PropertyData {
};

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
class PropertyDataT : public PropertyData {
    std::unique_ptr<T> _value = make_unique<T>();

public:
    T& get() { return *_value; }
    void set(T value) { *_value = value; }

    void bindTo(T* v) { _value = std::unique_ptr<T>(v); }
};

////
/// \brief property handling class for ui object.
/// \details this is different from CEAMMC library property handling library - later merge / unify that
class Property {

private:
    std::vector<Variant> _data;
    std::vector<Variant> _defaultData;

    bool _applyToPd; ///> true if property value should be passed to pd object

    std::function<void(void)> _action = []() {};
    inline void _updated() { _action(); }

    Variant _errorOut =Variant("ERR");
public:
    explicit Property();
    Property(const Property& src);
    Property(Property& src);

    const Property operator=(const Property& rval);
    Property operator=(Property& rval);

    // -------

    template <typename T>
    void set(T val);

    template <typename T>
    T as();

    template <typename T>
    bool is();

    template <typename T>
    void operator=(T val) { set(val); };

    void copyDataToDefault(); ///> copy current value to default value

    // -------
    void setAction(std::function<void(void)> action) { _action = action; }

    // -------
    Variant& componentAt(int idx)
    {
        if (idx >= _data.size())
            return _errorOut;//Variant(-1);
        return _data[idx];
    }
    // -------

    UIPropertyType type;
    bool readOnly;
    std::string group;
    std::string version;

    std::string asPdSaveString();
};

#endif // CM_PROPERTY_H
