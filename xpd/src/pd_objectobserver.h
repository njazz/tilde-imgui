#ifndef OBJECT_OBSERVER_H
#define OBJECT_OBSERVER_H

#include "observer.h"
#include "cpd/cpd_list.h"

namespace xpd {

/**
 * @brief The PdObjectObserver class
 * @details See Observer base class
 */
class PdObjectObserver : public Observer {
    t_cpd_list* _data;

public:
    PdObjectObserver();
    virtual ~PdObjectObserver();

    virtual void update();

    /// @brief Set data with CPD list
    void setData(t_cpd_list* data);
    /// @brief Get contents as CPD list
    t_cpd_list* data();
};

} // namespace xpd

#endif // OBSERVER_H
