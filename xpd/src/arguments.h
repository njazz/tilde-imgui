#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <mapbox/variant.hpp>
#include <string>
#include <vector>

namespace xpd {

/// @brief Float/String variant data type
typedef mapbox::util::variant<float, std::string> Arg;
/// @brief Variant type list
typedef std::vector<Arg> ArgList;

/**
 * @brief The Arguments class
 * @details List that contains variant type to be used with Objects/Canvases
 */
class Arguments {
protected:
    ArgList args_;

public:
    Arguments();
    explicit Arguments(float v);
    explicit Arguments(const std::string& s);
    virtual ~Arguments();

    /// @brief The list itself (const)
    const ArgList& args() const;
    /// @brief The list itself
    ArgList& args();

    /// @brief Add float
    void add(float f);
    /// @brief Add string
    void add(const std::string& s);

    /**
     * @brief Converts string to ArgList and stores its value
     * @details Splits the string by spaces and converts all numbers to floats
     * @param s
     */
    virtual void parseString(const std::string& s);

    /// @brief Clears data
    virtual void clear();

    template <class T>
    T get(size_t n) const
    {
        return args_[n].get<T>();
    }

    /// @brief Get string value at position
    const std::string& getStringAt(size_t n) const;
    /// @brief Get float value at position
    float getFloatAt(size_t n) const;
};

} // namespace xpd

#endif // ARGUMENTS_H
