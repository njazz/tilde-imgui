#ifndef ARRAY_H
#define ARRAY_H

#include "object.h"

namespace xpd {

/**
 * @brief The FloatArray class
 * @details Base class for Pd Array Object (see PdFloatArray)
 */
class FloatArray : public Object {
public:
    enum PlotStyle {
        PLOT_POINTS = 0,
        PLOT_LINES,
        PLOT_BEZIER
    };

public:
    FloatArray(const Canvas* parent, const std::string& name, size_t size);

    /**
     * @brief Returns OBJ_TYPE_ARRAY
     */
    virtual ObjectType type() const override;

    /**
     * @brief Returns array size
     */
    virtual size_t size() const;

    /**
     * @brief Checks if array is empty
     * @return true if empty, false otherwise
     */
    bool empty() const;

    /**
     * @brief Resizes array
     * @param sz - new size
     * @return true on success, false on error 
     */
    virtual bool resize(size_t sz);

    /**
     * @brief Returns float value at specified position
     * @param idx - position
     * @return float value
     * @throw Exception if wrong index is given
     */
    virtual float at(size_t idx) const;

    /**
     * @brief Returns array plot style
     */
    virtual PlotStyle plotStyle() const;

    /**
     * @brief Sets plot style
     * @param style - new plot style
     */
    virtual void setPlotStyle(PlotStyle style);

    /**
     * @brief Fill with value
     * @param v - fill value
     */
    virtual void fill(float v);

    virtual void registerObserver(Observer* o);
    virtual void unregisterObserver(Observer* o);

public:
    struct Exception : public std::runtime_error {
        Exception(const char* msg);
        Exception(const std::string& msg);
    };

protected:
    size_t size_;
    PlotStyle plot_style_;
};
}

#endif // ARRAY_H
