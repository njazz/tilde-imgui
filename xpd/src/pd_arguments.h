#ifndef PD_ARGUMENTS_H
#define PD_ARGUMENTS_H

#include "arguments.h"
#include "cpd/cpd_list.h"

namespace xpd {

/**
 * @brief The PdArguments class
 * @details see Arguments class
 */
class PdArguments : public Arguments {
    t_cpd_list* lst_;

public:
    PdArguments();
    PdArguments(const PdArguments&);
    explicit PdArguments(float v);
    explicit PdArguments(const std::string& s);
    explicit PdArguments(const Arguments& a);
    ~PdArguments();

    void operator=(const PdArguments&);

    void parseString(const std::string& s);

    void clear();

    /// @brief Get contents as CPD list
    const t_cpd_list* atomList() const;

    size_t size(){return cpd_list_size(lst_);}

private:
    void free();
};

} // namespace xpd

#endif // PD_ARGUMENTS_H
