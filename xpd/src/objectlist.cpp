#include "objectlist.h"
#include "logger.h"

namespace xpd {

ObjectList::ObjectList()
{
}

ObjectList::~ObjectList()
{
    clear();
}

const ConnectionList& ObjectList::connections() const
{
    return conn_;
}

bool ObjectList::append(Object* o)
{
    if (!o)
        return false;

    // check if already exists
    auto it = std::find(obj_.begin(), obj_.end(), o);
    if (it != obj_.end()) {
        log()->error("ObjectList::append: double insertion attempt ({})", static_cast<void*>(o));
        return false;
    }

    obj_.push_back(o);
    return true;
}

void ObjectList::clear()
{
    for (size_t i = 0; i < obj_.size(); i++)
        delete obj_[i];

    obj_.clear();
}

bool ObjectList::remove(ObjectId id)
{
    ssize_t pos = findObjectIndex(id);
    if (pos < 0)
        return false;

    delete obj_[pos];
    return removeIndex(pos);
}

bool ObjectList::removeIndex(size_t pos)
{
    if (pos >= obj_.size())
        return false;

    obj_[pos] = nullptr;
    obj_.erase(obj_.begin() + pos);
    return true;
}

bool ObjectList::empty() const
{
    return obj_.empty();
}

size_t ObjectList::size() const
{
    return obj_.size();
}

bool ObjectList::connect(ObjectId src, size_t srcOutletIdx, ObjectId dest, size_t destInletIdx)
{
    if (src == dest) {
        log()->error("ObjectList::connect: self-connection attempt {}->{}", src, dest);
        return false;
    }

    if (!checkObjectOutlet(src, srcOutletIdx))
        return false;

    if (!checkObjectInlet(dest, destInletIdx))
        return false;

    Connection c(src, srcOutletIdx, dest, destInletIdx);
    if (hasConnection(c)) {
        log()->error("ObjectList::connect: connection already exists");
        return false;
    }

    conn_.push_back(c);
    return true;
}

bool ObjectList::disconnect(ObjectId src, size_t srcOutletIdx, ObjectId dest, size_t destInletIdx)
{
    Connection c(src, srcOutletIdx, dest, destInletIdx);
    auto it = std::find(conn_.begin(), conn_.end(), c);
    if (it == conn_.end()) {
        log()->error("ObjectList::disconnect: connection not found");
        return false;
    }

    conn_.erase(it);
    return true;
}

bool ObjectList::isConnected(ObjectId obj1, ObjectId obj2) const
{
    auto it = std::find_if(conn_.begin(), conn_.end(),
        [obj1, obj2](const Connection& c) { return (c.src() == obj1 && c.dest() == obj2)
                                                || (c.src() == obj2 && c.dest() == obj1); });

    return it != conn_.end();
}

Object* ObjectList::findObject(ObjectId id)
{
    auto it = std::find_if(obj_.begin(), obj_.end(), [id](Object* o) { return o->id() == id; });
    return it == obj_.end() ? 0 : *it;
}

const Object* ObjectList::findObject(ObjectId id) const
{
    auto it = std::find_if(obj_.begin(), obj_.end(), [id](const Object* o) { return o->id() == id; });
    return it == obj_.end() ? 0 : *it;
}

ssize_t ObjectList::findObjectIndex(ObjectId id) const
{
    auto it = std::find_if(obj_.begin(), obj_.end(), [id](const Object* o) { return o->id() == id; });
    return it == obj_.end() ? -1 : std::distance(obj_.begin(), it);
}

bool ObjectList::contains(ObjectId id) const
{
    return findObject(id) != 0;
}

bool ObjectList::checkObjectInlet(ObjectId id, size_t n) const
{
    const Object* obj = findObject(id);
    if (!obj) {
        log()->error("ObjectList::checkObjectInlet: object not found in list - id:{}", id);
        return false;
    }

    if (!(n < obj->inletCount())) {
        log()->error("ObjectList::checkObjectInlet: invalid inlet index - {}, max values is {}",
            n, obj->inletCount());
        return false;
    }

    return true;
}

bool ObjectList::checkObjectOutlet(ObjectId id, size_t n) const
{
    const Object* obj = findObject(id);
    if (!obj) {
        log()->error("ObjectList::checkObjectOutlet: object not found in list - id:{}", id);
        return false;
    }

    if (!(n < obj->outletCount())) {
        log()->error("ObjectList::checkObjectOutlet: invalid outlet index - {}, max values is {}",
            n, obj->outletCount());
        return false;
    }

    return true;
}

bool ObjectList::hasConnection(const Connection& c) const
{
    return std::find(conn_.begin(), conn_.end(), c) != conn_.end();
}

} // namespace xpd
