// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_NEW_PROPERTY_H
#define CM_NEW_PROPERTY_H

#include <math.h>
#include <string>
#include <utility>
#include <vector>

#include <memory>

#include "IUAction.hpp"

#include <functional>

//typedef enum {
//    // empty
//    ptNull,
//    // basic
//    ptBool,
//    ptFloat,
//    ptInt,
//    ptSymbol,
//    ptString,
//    // arrays
//    ptList,
//    ptVector,
//    ptVec2,
//    ptColor,
//    ptStringList,
//    // specials
//    ptPath, ///> file or directory
//    ptPathList,
//    ptEnum, ///> index and option list
//    ptText ///< multiline text for comments, script

//} NewPropertyType;

template <typename T>
class PropertyT;

class PropertyBase {
    virtual void _abstractClass() = 0;
public:
    template <typename T>
    PropertyT<T>* typed()
    {

        return dynamic_cast<PropertyT<T>*>(this);

//        if ((PropertyT<T>*) this->is<T>()) {
//            return (PropertyT<T>*)this;
//        } else
//            return 0;
    }

    //
    std::function<void(void)> _action = []() {};
    inline void _updated() { _action(); }
    void setAction(std::function<void(void)> action) { _action = action; }
};

template <typename T>
class PropertyT : public PropertyBase {
    virtual void _abstractClass() override {};
    T* _data = 0;
    T _defaultValue;
    bool _internal = false;

public:
    PropertyT(T* ref = 0)
    {
        if (!ref) {
            _data = new T;
            _internal = true;
        } else {
            _data = ref;
        }
    }

    ~PropertyT()
    {
        if (_internal)
            delete _data;
    }

    void set(T d)
    {
        *_data = d;
        _updated();
    }
    T get() { return *_data; }

    template <typename U>
    bool is() { return typeid(T) == typeid(U); }

    void setDefaultValue(T v)
    {
        _defaultValue = v;
    };

    //
    bool readOnly = false;
    std::string group = "";
    std::string version = "";

    //
    std::string asPdString() { return "(unsupported)"; }
};

////

//template <int S>
//class FVecPtr
//{
//  std::vector<float*> _data;
//public:
//FVecPtr()
// {
//    if (!s) return;

//    for (int i=0;i<s;i++)

// }

//};

#endif // CM_PROPERTY_H
