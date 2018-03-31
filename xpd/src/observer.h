#ifndef OBSERVER_H
#define OBSERVER_H

namespace xpd {

/**
 * @brief The Observer class
 * @details Base class for observers
 */
class Observer {
public:
    Observer();
    virtual ~Observer();

    virtual void update();
};

} // namespace xpd

#endif // OBSERVER_H
