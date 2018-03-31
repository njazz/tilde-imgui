#include "canvas.h"
#include "logger.h"

#include <algorithm>

namespace xpd {

Canvas::Canvas(const Canvas* parent, const CanvasSettings& s)
    : Object(parent, s.name())
    , settings_(s)
{
}

const CanvasSettings& Canvas::settings() const
{
    return settings_;
}

const std::string& Canvas::path() const
{
    return path_;
}

void Canvas::registerObserver(CanvasObserverPtr o)
{
}

void Canvas::deleteObserver(CanvasObserverPtr o)
{
}

const ObjectList& Canvas::objects() const
{
    return obj_list_;
}

bool Canvas::connect(ObjectId, size_t outletIdx, ObjectId dest, size_t inletIdx)
{
    return false;
}

bool Canvas::disconnect(ObjectId src, size_t outletIdx, ObjectId dest, size_t inletIdx)
{
    return false;
}

bool Canvas::deleteObject(ObjectId objId)
{
    return obj_list_.remove(objId);
}

bool Canvas::hasChildren() const
{
    return !obj_list_.empty();
}

size_t Canvas::childrenCount() const
{
    return obj_list_.size();
}

const ObjectList& Canvas::children() const
{
    return obj_list_;
}

void Canvas::removeAllChildren()
{
    obj_list_.clear();
}

ObjectType Canvas::type() const
{
    return OBJ_TYPE_CANVAS;
}

void Canvas::sendBang(ObjectId id)
{
    Object* o = obj_list_.findObject(id);
    if (!o) {
        log()->error("Canvas::sendBang: invalid object ID {}", id);
        return;
    }

    o->sendBang();
}

void Canvas::sendFloat(ObjectId id, float f)
{
    Object* o = obj_list_.findObject(id);
    if (!o) {
        log()->error("Canvas::sendFloat: invalid object ID {}", id);
        return;
    }

    o->sendFloat(f);
}

void Canvas::loadbang()
{
    log()->warn("Canvas::loadbang() is not implemented");
}

bool Canvas::isRoot() const
{
    return !parent();
}

std::vector<std::string> Canvas::availableObjects() const
{
    return std::vector<std::string>();
}

CanvasSettings::CanvasSettings(const std::string& name, int x, int y, size_t w, size_t h)
    : name_(name)
    , x_(std::max(0, x))
    , y_(std::max(0, y))
    , w_(w)
    , h_(h)
{
}

const std::string& CanvasSettings::name() const
{
    return name_;
}

} // namespace xpd
