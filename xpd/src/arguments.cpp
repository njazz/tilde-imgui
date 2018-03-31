#include "arguments.h"

namespace xpd {

Arguments::Arguments()
{
}

Arguments::Arguments(float v)
{
    args_.push_back(v);
}

Arguments::Arguments(const std::string& s)
{
    args_.push_back(s);
}

Arguments::~Arguments()
{
}

const ArgList& Arguments::args() const
{
    return args_;
}

ArgList& Arguments::args()
{
    return args_;
}

void Arguments::add(float f)
{
    args_.push_back(f);
}

void Arguments::add(const std::string& s)
{
    args_.push_back(s);
}

void Arguments::parseString(const std::string& s)
{
    args_.push_back(s);
}

void Arguments::clear()
{
    args_.clear();
}

const std::string& Arguments::getStringAt(size_t n) const
{
    return args_[n].get<std::string>();
}

float Arguments::getFloatAt(size_t n) const
{
    return get<float>(n);
}

} // namespace xpd
