#ifndef CONNECTION_H
#define CONNECTION_H

#include <memory>

#include "object.h"

namespace xpd {

class Canvas;

/**
 * @brief The Connection class
 * @details Represents connection but doesn't create it
 */
class Connection {
    ObjectId src_, dest_;
    int src_out_, dest_in_;

public:
    Connection(ObjectId src, int outln, ObjectId dest, int inln);

    ObjectId src() const { return src_; }
    ObjectId dest() const { return dest_; }

    bool operator==(const Connection& c) const
    {
        return src_ == c.src_
            && dest_ == c.dest_
            && src_out_ == c.src_out_
            && dest_in_ == c.dest_in_;
    }
};

} // namespace xpm

#endif // CONNECTION_H
