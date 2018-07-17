#include "UIObjectsLibrary.h"
#include "UIObjectFactory.h"

#include "UIObject.hpp"

#include "UIBang.h"
#include "UIDSP.h"
#include "UIFloat.h"
#include "UIMatrix.h"
#include "UIMessage.h"
#include "UISlider.h"
#include "UIToggle.h"

void setupUIObjectsLibrary()
{
    UIObjectFactory::registerClass<UIObject>("*");

    UIObjectFactory::registerClass<UIBang>("ui.bang");
    UIObjectFactory::registerClass<UIToggle>("ui.toggle");
    UIObjectFactory::registerClass<UIMessage>("ui.msg");
    UIObjectFactory::registerClass<UIFloat>("ui.float");
    UIObjectFactory::registerClass<UISlider>("ui.slider");
    UIObjectFactory::registerClass<UIDSP>("ui.dsp");
    UIObjectFactory::registerClass<UIMatrix>("ui.matrix");
}
