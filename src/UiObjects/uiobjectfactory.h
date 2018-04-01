#ifndef UIOBJECTFACTORY_H
#define UIOBJECTFACTORY_H

#include "UiObjects/UIObject.hpp"

#include "UiObjects/UIBang.h"
#include "UiObjects/UIToggle.h"
#include "UiObjects/UIMessage.h"
#include "UiObjects/UIFloat.h"

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
    static void registerAll()
    {
        registerClass<UIObject>("*");

        registerClass<UIBang>("ui.bang");
        registerClass<UIToggle>("ui.toggle");
        registerClass<UIMessage>("ui.msg");
        registerClass<UIFloat>("ui.float");

    }

    template <typename T>
    static void registerClass(std::string className)
    {
        _c[className] = new _typeConstructor<T>;
    }

    static ObjectBase* createUiObject(std::string className)
    {
        printf("factory <%s>\n", className.c_str());

        if (_c[className])
        {
            printf("created %s\n", className.c_str());
            return (*_c[className])();
        }

        return new UIObject;//(*_c["*"])();
    }
};

#endif // UIOBJECTFACTORY_H
