#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "arguments.h"
#include "objectproperties.h"
#include "xlets.h"

namespace xpd {

class Canvas;
class Observer;
class ClassInfo;
class Object;
class ObjectList;

typedef std::unique_ptr<Object> ObjectPtr;
typedef std::vector<Inlet> InletList;
typedef std::vector<Outlet> OutletList;
typedef std::shared_ptr<Observer> ObserverPtr;
typedef std::shared_ptr<ClassInfo> ClassInfoPtr;

enum ObjectType {
    OBJ_TYPE_SIMPLE_BOX = 0,
    OBJ_TYPE_ERROR_BOX,
    OBJ_TYPE_CANVAS,
    OBJ_TYPE_ARRAY,
    OBJ_TYPE_ABSTRACTION,
    OBJ_TYPE_GUI
};

typedef size_t ObjectId;

/**
 * @brief The Object class
 * @details Base class, see PdObject
 */
class Object {
    /// @brief Object Id counter. One per Server (library)
    static size_t id_counter_;

protected:
    std::string name_;
    const Canvas* parent_;
    InletList inlet_list_;
    OutletList outlet_list_;
    ClassInfoPtr class_;
    ObjectId id_;
    int x_, y_;
    std::vector<ObserverPtr> observers_;

    /// @brief Create new object Id
    static ObjectId generateNewId();

public:
    typedef std::runtime_error Exception;

public:
    Object(const Canvas* parent, const std::string& name, int x = 0, int y = 0);
    virtual ~Object();

    const std::string& name() const;
    const Canvas* parent() const;

    virtual const Arguments& arguments() const;

    /// @brief Returns object inlet count
    virtual size_t inletCount() const;
    /// @brief Returns object outlet count
    virtual size_t outletCount() const;

    /// @brief Returns OBJ_TYPE_SIMPLE_BOX
    virtual ObjectType type() const;
    /// @brief Sets object type (?)
    virtual void setType(ObjectType type);

    /// @brief Add new observer
    virtual void registerObserver(ObserverPtr o);
    /// @brief Remove observer from list
    virtual void deleteObserver(ObserverPtr o);

    /// @brief Inlet object list
    const InletList& inlets() const;
    /// @brief Outlet object list
    const OutletList& outlets() const;

    /// @brief Properties object
    virtual const ObjectProperties& properties() const;

    /// @brief Object Id
    ObjectId id() const;

    virtual bool isRoot() const;
    virtual bool hasChildren() const;
    virtual size_t childrenCount() const;
    virtual const ObjectList& children() const;
    virtual void removeAllChildren();

    int x() const;
    int y() const;

    virtual void setX(int x);
    virtual void setY(int y);

    virtual void sendBang();
    virtual void sendFloat(float f);
    virtual void sendSymbol(const std::string& s);
    virtual void sendList(const Arguments a);

    virtual Canvas* asCanvas();
    virtual const Canvas* asCanvas() const;

private:
    Object(const Object&);
    void operator=(const Object&);
};

// temporary
//t_object* _pdObject;
//bool hasInternalObject() { return _pdObject != 0; }

//void message(string str);
//ServerCanvas* toServerCanvas();
//void setReceiveSymbol(string symbolName);

} // namespace xpd

#endif // OBJECT_H
