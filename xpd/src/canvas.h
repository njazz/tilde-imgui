#ifndef SERVERCANVAS_H
#define SERVERCANVAS_H

#include <memory>
#include <string>
#include <vector>

#include "connection.h"
#include "object.h"
#include "objectlist.h"

namespace xpd {

class CanvasObserver;
typedef std::shared_ptr<CanvasObserver> CanvasObserverPtr;
typedef std::vector<CanvasObserverPtr> CanvasObserverList;

/**
 * @brief The CanvasSettings class
 */
class CanvasSettings {
    std::string name_;
    int x_, y_;
    size_t w_, h_;

public:
    CanvasSettings(const std::string& name, int x = 0, int y = 0, size_t w = 600, size_t h = 400);
    const std::string& name() const;

    int x() const { return x_; }
    int y() const { return y_; }
    size_t width() const { return w_; }
    size_t height() const { return h_; }
};

/**
 * @brief The Canvas class
 * @details Base class for Pd Canvas object (see PdCanvas)
 */
class Canvas : public Object {
protected:
    CanvasSettings settings_;
    std::string path_;
    CanvasObserverList observer_list_;
    ObjectList obj_list_;

public:
    /// @brief Create new Canvas with parent and settings
    Canvas(const Canvas* parent, const CanvasSettings& s);
    const CanvasSettings& settings() const;

    /// @brief Returns canvas file path.
    virtual const std::string& path() const;

    void registerObserver(CanvasObserverPtr o);
    void deleteObserver(CanvasObserverPtr o);

    const ObjectList& objects() const;

    virtual bool connect(ObjectId, size_t outletIdx, ObjectId dest, size_t inletIdx);
    virtual bool disconnect(ObjectId src, size_t outletIdx, ObjectId dest, size_t inletIdx);

    virtual ObjectId createObject(const std::string& name, int x, int y) = 0;
    virtual bool deleteObject(ObjectId objId);

    /**
     * @brief Creates new array and appends it to child list
     * @param name - array name
     * @param size - array size
     * @return array ID
     */
    virtual ObjectId createArray(const std::string& name, size_t size) = 0;

    virtual bool hasChildren() const override;
    virtual size_t childrenCount() const override;
    virtual const ObjectList& children() const override;
    virtual void removeAllChildren() override;

    virtual ObjectType type() const override;

    void sendBang(ObjectId id);
    void sendFloat(ObjectId id, float f);

    /**
     * @brief Sends loadbang to all objects
     */
    virtual void loadbang();

    /**
     * @brief If canvas has no parents - it's root canvas
     */
    virtual bool isRoot() const override;

    virtual std::vector<std::string> availableObjects() const;
};

//    vector<ServerPatchcord*> _patchcords;
//    ServerInstance* _parentInstance;
//    struct _glist* canvasObject();
//    ServerCanvas* createEmptySubCanvas();
//    ServerObject* toServerObject();

} // namespace xpd

#endif // SERVERCANVAS_H
