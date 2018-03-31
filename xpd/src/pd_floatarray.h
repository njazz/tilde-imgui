#ifndef PdFloatArray_H
#define PdFloatArray_H

#include "array.h"
#include "pd_floatarraydata.h"

#include "cpd/cpd_types.h"

#include <iterator>

namespace xpd {

/**
 * @brief The PdFloatArray class
 * @details See FloatArray
 */
class PdFloatArray : public FloatArray {
    t_cpd_canvas* cnv_;
    t_cpd_array* arr_;
    Observer* _observer;

public:
    PdFloatArray(const Canvas* parent, const std::string& name, size_t size);
    ~PdFloatArray();

    PdFloatArrayData* getData();

    virtual float at(size_t idx) const override;
    virtual bool resize(size_t sz) override;
    virtual void setPlotStyle(PlotStyle style) override;
    virtual void fill(float v) override;

    // virtual ObjectId createObject(const std::string& name, int x, int y) override {return 0;};

public:
    typedef typename std::allocator<float>::difference_type difference_type;
    typedef typename std::allocator<float>::value_type value_type;
    typedef typename std::allocator<float>::reference reference;
    typedef typename std::allocator<float>::const_reference const_reference;
    typedef typename std::allocator<float>::pointer pointer;
    typedef typename std::allocator<float>::const_pointer const_pointer;
    typedef typename std::allocator<float>::size_type size_type;

    class iterator {
        t_cpd_array_element* el_;

    public:
        typedef typename std::allocator<float>::difference_type difference_type;
        typedef typename std::allocator<float>::value_type value_type;
        typedef typename std::allocator<float>::reference reference;
        typedef typename std::allocator<float>::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category;

        iterator(t_cpd_array_element* el);
        iterator(const iterator&);

        iterator& operator=(const iterator&);
        bool operator==(const iterator& it) const { return el_ == it.el_; }
        bool operator!=(const iterator& it) const { return el_ != it.el_; }
        bool operator<(const iterator& it) const { return el_ < it.el_; }
        bool operator>(const iterator& it) const { return el_ > it.el_; }
        bool operator<=(const iterator& it) const { return el_ <= it.el_; }
        bool operator>=(const iterator& it) const { return el_ >= it.el_; }

        //        friend void swap(iterator& lhs, iterator& rhs);

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator& operator+=(size_type);
        iterator operator+(size_type) const;
        iterator& operator-=(size_type);
        iterator operator-(size_type) const;
        difference_type operator-(iterator) const;

        reference operator*() const;
        reference operator[](size_type) const;
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;

    iterator begin();
    const iterator begin() const;
    iterator end();
    const iterator end() const;
    reverse_iterator rbegin();
    reverse_iterator rend();

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
};

} // namespace xpd

#endif // PdFloatArray_H
