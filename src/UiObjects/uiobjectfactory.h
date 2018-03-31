#ifndef UIOBJECTFACTORY_H
#define UIOBJECTFACTORY_H

#include "views/NodeObject.hpp"

typedef ObjectBase* (*objectBaseConstructor)();

class _typeConstructorBase {
public:
    virtual ObjectBase* operator()() = 0;
};

template <typename T>
class _typeConstructor : public _typeConstructorBase {
public:
    virtual T* operator()() override { return new T(); }
};

class UIObjectFactory {
    static std::map<std::string, _typeConstructorBase*> _c;

public:
    UIObjectFactory()
    {
        registerClass<NodeObject>("*");
    }

    template <typename T>
    static void registerClass(std::string className)
    {
        _c[className] = new _typeConstructor<T>;
    }

    static ObjectBase* createUiObject(std::string className)
    {
        if (_c[className])
        {
            return (*_c[className])();
        }

        return new NodeObject;//(*_c["*"])();
    }
};

#endif // UIOBJECTFACTORY_H
