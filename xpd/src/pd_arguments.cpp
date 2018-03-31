#include "pd_arguments.h"

namespace xpd {

PdArguments::PdArguments()
    : lst_(cpd_list_new(0))
{
}

PdArguments::PdArguments(const PdArguments& a)
    : Arguments(a)
    , lst_(cpd_list_copy(a.lst_))
{
}

PdArguments::PdArguments(float v)
    : Arguments(v)
    , lst_(cpd_list_new(1))
{
    cpd_atom_set_float(cpd_list_at(lst_, 0), v);
}

PdArguments::PdArguments(const std::string& s)
    : Arguments(s)
    , lst_(cpd_list_new(1))
{
    cpd_atom_set_string(cpd_list_at(lst_, 0), s.c_str());
}

PdArguments::PdArguments(const Arguments& a)
{
    size_t s = a.args().size();

    lst_ = cpd_list_new(s);

    for (int i = 0; i < s; i++) {
        Arg ar = a.args().at(i);
        if (ar.is<float>())
            cpd_list_set_float_at(lst_, i, ar.get<float>());

        if (ar.is<std::string>())
            cpd_list_set_symbol_at(lst_, i, cpd_symbol(ar.get<std::string>().c_str()));
    }
}

PdArguments::~PdArguments()
{
    free();
}

void PdArguments::operator=(const PdArguments& a)
{
    args_ = a.args_;
    cpd_list_free(lst_);
    lst_ = cpd_list_copy(a.lst_);
}

void PdArguments::parseString(const std::string& s)
{
    free();
    lst_ = cpd_list_new_from_string(s.c_str());
    const size_t N = cpd_list_size(lst_);

    for (size_t i = 0; i < N; i++) {
        auto a = cpd_list_at(lst_, i);

        if (cpd_atom_is_float(a))
            args_.push_back(cpd_atom_get_float(a));

        if (cpd_atom_is_symbol(a)) {
            auto s = cpd_atom_get_symbol(a);
            args_.push_back(std::string(cpd_symbol_name(s)));
        }
    }
}

void PdArguments::clear()
{
    args_.clear();
    cpd_list_clear(lst_);
}

const t_cpd_list* PdArguments::atomList() const
{
    return lst_;
}

void PdArguments::free()
{
    args_.clear();
    cpd_list_free(lst_);
    lst_ = 0;
}

} // namespace xpd
