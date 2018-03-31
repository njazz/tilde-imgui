#include "array.h"

using namespace xpd;

FloatArray::FloatArray(const Canvas* parent, const std::string& name, size_t size)
    : Object(parent, name)
    , size_(size)
    , plot_style_(PLOT_LINES)
{
}

ObjectType FloatArray::type() const
{
    return OBJ_TYPE_ARRAY;
}

size_t FloatArray::size() const
{
    return size_;
}

bool FloatArray::empty() const
{
    // virtual call
    return size() == 0;
}

bool FloatArray::resize(size_t sz)
{
    if (sz == size_)
        return true;

    return false;
}

float FloatArray::at(size_t idx) const
{
    throw Exception("not implemented");
}

FloatArray::PlotStyle FloatArray::plotStyle() const
{
    return plot_style_;
}

void FloatArray::setPlotStyle(FloatArray::PlotStyle style)
{
    plot_style_ = style;
}

void FloatArray::fill(float v)
{
    throw Exception("not implemented");
}

void FloatArray::registerObserver(Observer* o)
{
}

void FloatArray::unregisterObserver(Observer* o)
{
}

FloatArray::Exception::Exception(const char* msg)
    : std::runtime_error(msg)
{
}

FloatArray::Exception::Exception(const std::string& msg)
    : std::runtime_error(msg)
{
}
