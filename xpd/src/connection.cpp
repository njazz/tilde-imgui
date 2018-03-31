#include "connection.h"

using namespace xpd;

Connection::Connection(ObjectId src, int outln, ObjectId dest, int inln)
    : src_(src)
    , dest_(dest)
    , src_out_(outln)
    , dest_in_(inln)
{
}
