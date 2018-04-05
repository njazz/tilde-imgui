#include "pd_objectobserver.h"

namespace xpd {

PdObjectObserver::PdObjectObserver()
{
    _data = PdArguments();
}

PdObjectObserver::~PdObjectObserver()
{
}

void PdObjectObserver::update()
{
}

//void PdObjectObserver::setData(t_cpd_list* data)
//{
//    _data = data;
//}
//t_cpd_list* PdObjectObserver::data()
//{
//    return _data;
//}

} // namespace xpd
