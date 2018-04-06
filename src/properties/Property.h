// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_PROPERTY_H
#define CM_PROPERTY_H

#include <math.h>
#include <string>
#include <utility>
#include <vector>

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
    int _intValue;
    float _floatValue;
    std::string _stringValue;

    int* _intPtr = &_intValue;
    float* _floatPtr = &_floatValue;
    std::string* _stringPtr = &_stringValue;

public:
    Variant(int v);
    Variant(long v);
    Variant(bool b);
    Variant(float f);
    Variant(double f);
    Variant(std::string s);

    template <typename T>
    void set(T val)
    {
        // TODO
    }

    template <typename T>
    T get()
    {
        // let's try lol
        return (T)*_floatPtr;
    };

    void bindInt(int* p) { _intPtr = p; }
    void bindFloat(float* p) { _floatPtr = p; }
    void bindString(std::string* p) { _stringPtr = p; }
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
    Variant componentAt(int idx)
    {
        if (idx >= _data.size())
            return Variant(-1);
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
