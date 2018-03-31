#ifndef XLETS_H
#define XLETS_H

namespace xpd {

enum XletType {
    XLET_MESSAGE = 0,
    XLET_SIGNAL
};

/**
 * @brief The Xlet class
 * @details Base class for Inlet and Outlet
 */
class Xlet {
    XletType type_;

public:
    Xlet(XletType t);
    XletType type() const;  /// @brief Message or signal
};

/**
 * @brief The object Inlet class
 */
class Inlet : public Xlet {
public:
    Inlet(XletType t);
};

/**
 * @brief The object Outlet class
 */
class Outlet : public Xlet {
public:
    Outlet(XletType t);
};

} // namespace xpd

#endif // XLETS_H
