#ifndef CLASSINFO_H
#define CLASSINFO_H

#include <string>

namespace xpd {

/**
 * @brief The ClassInfo class
 * @details Stores information about Pd class (object name and library)
 */
class ClassInfo {
    std::string name_;
    std::string library_;

public:
    ClassInfo(const std::string& name);

    /// @brief Returns name
    const std::string& name() const;
    /// @brief Returns library name
    const std::string& library() const;
};

} // namespace xpd

#endif // CLASSINFO_H
