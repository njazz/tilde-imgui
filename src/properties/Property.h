// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_PROPERTY_H
#define CM_PROPERTY_H

#include <math.h>
#include <string>
#include <utility>
#include <vector>

#include "IUObserver.hpp"

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
        return (T)_floatValue;
    };
};


////
/// \brief property handling class for ui object.
/// \details this is different from CEAMMC library property handling library - later merge / unify that
class Property {

private:
    std::vector<Variant> _data;
    std::vector<Variant> _defaultData;

    bool _applyToPd; ///> true if property value should be passed to pd object

    IUObserver _action;

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

    void copyDataToDefault(); ///> copy current value to default value

    // -------
    void setAction(IUObserver action) { _action = action; }

    // -------

    UIPropertyType type;
    bool readOnly;
    std::string group;
    std::string version;

    std::string asPdSaveString();
};

#endif // CM_PROPERTY_H
