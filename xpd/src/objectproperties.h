#ifndef OBJECTPROPERTIES_H
#define OBJECTPROPERTIES_H

#include <memory>
#include <vector>

namespace xpd {

class PropertyObserver;
typedef std::shared_ptr<PropertyObserver> PropertyObserverPtr;
typedef std::vector<PropertyObserver> PropertyObserverList;

/**
 * @brief The ObjectProperties class
 */
class ObjectProperties {
    PropertyObserverList observer_list_;

public:
    ObjectProperties();

    void registerObserver(PropertyObserverPtr ptr);
    void deleteObserver(PropertyObserverPtr ptr);
};

} // namespace xpd

#endif // OBJECTPROPERTIES_H
