#ifndef LIBRARYINFO_H
#define LIBRARYINFO_H

#include <string>

namespace xpd {

/**
 * @brief The LibraryInfo class
 * @details Information about Pd library
 */
class LibraryInfo {
    std::string name_;
    std::string version_;

public:
    LibraryInfo(const std::string& name);
    /// @brief Pd library name
    const std::string& name() const;
    /// @brief Pd library version
    const std::string& version() const;
};

} // namespace xpd

#endif // LIBRARYINFO_H
