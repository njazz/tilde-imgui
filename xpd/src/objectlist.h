#ifndef OBJECTLIST_H
#define OBJECTLIST_H

#include "connection.h"
#include "object.h"

#include <vector>

namespace xpd {

typedef std::vector<Connection> ConnectionList;

class ObjectList {
    std::vector<Object*> obj_;
    ConnectionList conn_;

public:
    ObjectList();
    ~ObjectList();

    const std::vector<Object*>& get() const { return obj_; }
    std::vector<Object*>& get() { return obj_; }

    const ConnectionList& connections() const;

    /**
     * @brief Appends object to object list
     * @return true on success, false on error
     */
    bool append(Object* o);
    void clear();
    bool remove(ObjectId id);
    bool removeIndex(size_t pos);

    bool empty() const;
    size_t size() const;

    bool connect(ObjectId src, size_t srcOutletIdx, ObjectId dest, size_t destInletIdx);
    bool disconnect(ObjectId src, size_t srcOutletIdx, ObjectId dest, size_t destInletIdx);
    bool isConnected(ObjectId obj1, ObjectId obj2) const;

    Object* findObject(ObjectId id);
    const Object* findObject(ObjectId id) const;

    /**
     * @brief Returns object index or -1 if not found
     * @param id - object id 
     */
    ssize_t findObjectIndex(ObjectId id) const;

    /**
     * @brief Checks list contains object with specified ID
     * @param id - search id
     * @return true on success, otherwise false
     */
    bool contains(ObjectId id) const;

private:
    bool checkObjectInlet(ObjectId id, size_t n) const;
    bool checkObjectOutlet(ObjectId id, size_t n) const;
    bool hasConnection(const Connection& c) const;
};

} // namespace xpd

#endif // OBJECTLIST_H
