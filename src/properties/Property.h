// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_NEW_PROPERTY_H
#define CM_NEW_PROPERTY_H

#include <math.h>
#include <string>
#include <utility>
#include <vector>

#include "IUAction.hpp"
#include <functional>
#include <memory>

template <typename T>
class PropertyT;

class PropertyBase {
    virtual void _abstractClass() = 0;

public:
    template <typename T>
    PropertyT<T>* typed();

    //
    std::function<void(void)> _action = []() {};
    inline void _updated() { _action(); }
    void setAction(std::function<void(void)> action) { _action = action; }

    virtual bool isDefault() { return true; }
    virtual std::string asPdString() { return "(unsupported)"; }
};

template <typename T>
class PropertyT : public PropertyBase {
    virtual void _abstractClass() override{};
    T* _data = 0;
    T _defaultValue;
    bool _internal = false;

public:
    PropertyT(T* ref = 0);

    ~PropertyT();

    void set(T d);
    T get();

    template <typename U>
    bool is();

    void setDefaultValue(T v);
    void reset()
    {
        *_data = _defaultValue;
        _updated();
    }
    virtual bool isDefault() override { return *_data == _defaultValue; }

    //
    bool readOnly = false;
    std::string group = "";
    std::string version = "";

    //
    virtual std::string asPdString() override { return "(unsupported)"; }

    //
};

// ----------

template <typename T>
PropertyT<T>* PropertyBase::typed()
{
    return dynamic_cast<PropertyT<T>*>(this);
}

//

template <typename T>
PropertyT<T>::PropertyT(T* ref)
{
    if (!ref) {
        _data = new T;
        _internal = true;
    } else {
        _data = ref;
    }
}

template <typename T>
PropertyT<T>::~PropertyT()
{
    if (_internal)
        delete _data;
}

template <typename T>
void PropertyT<T>::set(T d)
{
    *_data = d;
    _updated();
}

template <typename T>
T PropertyT<T>::get() { return *_data; }

template <typename T>
template <typename U>
bool PropertyT<T>::is() { return typeid(T) == typeid(U); }

template <typename T>
void PropertyT<T>::setDefaultValue(T v)
{
    _defaultValue = v;
    *_data = v;
};

// ---

template <>
std::string PropertyT<float>::asPdString();

template <>
std::string PropertyT<float*>::asPdString();

template <>
std::string PropertyT<int>::asPdString();

template <>
std::string PropertyT<int*>::asPdString();

#endif // CM_PROPERTY_H
