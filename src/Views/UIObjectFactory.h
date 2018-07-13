#ifndef UIOBJECTFACTORY_H
#define UIOBJECTFACTORY_H

#include "UIObject.hpp"

#include "UIBang.h"
#include "UIToggle.h"
#include "UIMessage.h"
#include "UIFloat.h"
#include "UISlider.h"
#include "UIDSP.h"
#include "UIMatrix.h"

typedef UiObjectBase* (*objectBaseConstructor)();

class _typeConstructorBase {
public:
    virtual UiObjectBase* operator()() = 0;
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
        registerClass<UISlider>("ui.slider");
        registerClass<UIDSP>("ui.dsp");
        registerClass<UIMatrix>("ui.matrix");

    }

    template <typename T>
    static void registerClass(std::string className)
    {
        _c[className] = new _typeConstructor<T>;
    }

    static UiObjectBase* createUiObject(std::string className)
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
