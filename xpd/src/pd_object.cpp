#include "pd_object.h"
#include "pd_canvas.h"
#include "pd_localprocess.h"

#include "logger.h"

#include "cpd/cpd_object.h"
#include "cpd/cpd_types.h"

namespace xpd {

PdObject::PdObject(const Canvas* parent, const std::string& name, const PdArguments& args, int x, int y)
    : Object(parent, name, x, y)
    , cnv_(0)
    , obj_(0)
    , inlet_n_(0)
    , outlet_n_(0)
    , args_(args)
{
    const PdCanvas* pd_canvas = dynamic_cast<const PdCanvas*>(parent);
    if (!pd_canvas) {
        throw Exception("PdObject: invalid canvas pointer given. PdCanvas* expected");
    }

    cnv_ = const_cast<t_cpd_canvas*>(pd_canvas->canvas());
    if (!cnv_) {
        throw Exception("PdObject: NULL canvas pointer");
    }

    obj_ = cpd_object_new(cnv_, name.c_str(), args.atomList(), x, y);
    if (!obj_) {
        throw Exception("PdObject: can't create object");
    }

    // cache xlet number, since it should not change after object creation
    inlet_n_ = cpd_object_inlet_count(obj_);
    outlet_n_ = cpd_object_outlet_count(obj_);

    for (int i = 0; i < inlet_n_; i++) {
        XletType t = (cpd_object_inlet_type(obj_, i) == CPD_CONNECTION_SIGNAL) ? XLET_SIGNAL : XLET_MESSAGE;
        Inlet n = Inlet(t);

        inlet_list_.push_back(n);
    }

    for (int i = 0; i < outlet_n_; i++) {
        XletType t = (cpd_object_outlet_type(obj_, i) == CPD_CONNECTION_SIGNAL) ? XLET_SIGNAL : XLET_MESSAGE;
        Outlet n = Outlet(t);

        outlet_list_.push_back(n);
    }

    observer_ = 0;
}

PdObject::~PdObject()
{
    cpd_object_free(cnv_, obj_);
}

void PdObject::setX(int x)
{
    Object::setX(x);
    cpd_object_set_xpos(obj_, x);
}

void PdObject::setY(int y)
{
    Object::setY(y);
    cpd_object_set_ypos(obj_, y);
}

size_t PdObject::inletCount() const
{
//    if (cpd_is_canvas(obj_))
//        return cpd_object_inlet_count(obj_);

    return inlet_n_;
}

size_t PdObject::outletCount() const
{
//    if (cpd_is_canvas(obj_))
//        return cpd_object_outlet_count(obj_);

    return outlet_n_;
}

const Arguments& PdObject::arguments() const
{
    return args_;
}

t_cpd_object* PdObject::pdObject()
{
    return obj_;
}

ObjectType PdObject::type() const
{
    if (!obj_)
        return OBJ_TYPE_ERROR_BOX;

    if (cpd_is_canvas(obj_))
        return OBJ_TYPE_CANVAS;
    else
        return OBJ_TYPE_SIMPLE_BOX;
}

void PdObject::sendBang()
{
    cpd_send_bang(obj_);
}

void PdObject::sendFloat(float f)
{
    cpd_send_float(obj_, f);
}

void PdObject::sendSymbol(const std::string& s)
{
}

void PdObject::setReceiveSymbol(const std::string& s)
{
    cpd_bind_object(obj_, cpd_symbol(s.c_str()));
}

void PdObject::registerObserver(ObserverPtr o)
{
    observer_ = std::static_pointer_cast<PdObjectObserver>(o);
    PdLocalProcess::objectObserverMap[pdObject()] = observer_;
}
void PdObject::deleteObserver(ObserverPtr)
{
    observer_ = 0;
    PdLocalProcess::objectObserverMap[pdObject()] = 0;
}

void PdObject::sendList(const Arguments a)
{
    PdArguments pa(a);

    t_cpd_list* l = const_cast<t_cpd_list*>(pa.atomList());

    t_cpd_symbol* sel = cpd_list_get_symbol_at(l, 0);

    if (!sel) {
        cpd_send_list(obj_, l);
    } else {
        t_cpd_list* l2 = cpd_list_new(0);
        for (int i = 1; i < cpd_list_size(l); i++) {
            cpd_list_append(l2, cpd_list_at(l, i));
        }
        cpd_send_message(obj_, sel, l2);
    }
}

void PdObject::sendStringAsList(std::string s)
{
    t_cpd_list* l = cpd_list_new_from_string(s.c_str());

    t_cpd_symbol* sel = cpd_list_get_symbol_at(l, 0);

    if (!sel) {
        cpd_send_list(obj_, l);
    } else {
        t_cpd_list* l2 = cpd_list_new(0);
        for (int i = 1; i < cpd_list_size(l); i++) {
            cpd_list_append(l2, cpd_list_at(l, i));
        }
        cpd_send_message(obj_, sel, l2);
    }
}

PdCanvas* PdObject::asPdCanvas()
{

    bool isCanvas;
    PdCanvas* ret = 0;

    if (!obj_) {
        isCanvas = false;
        log()->error("to_server_canvas: bad canvas object!");
        return ret;
    } else
        isCanvas = cpd_is_canvas(obj_);

    if (isCanvas) {
        CanvasSettings settings = CanvasSettings("< subpatch >");
        ret = new PdCanvas(settings, obj_);
    } else {
        log()->error("object is not a canvas!");
    }

    return ret;
}

size_t PdObject::childrenCount() const
{
    if (!obj_)
        return 0;

    if (!cpd_is_canvas(obj_))
        return 0;

    return cpd_canvas_object_count((t_cpd_canvas*)obj_);
}

//ObjectId PdObject::createObject(const std::string& name, int x, int y)
//{
//    if (!cpd_is_canvas(obj_))
//        return 0;

//    PdCanvas* c = static_cast<PdCanvas*>(asCanvas());

//    if (!c)
//        return 0;

//    return c->createObject(name,x,y);
//}

//Canvas* PdObject::asCanvas() const
//{
//    return (type() == OBJ_TYPE_CANVAS) ? (Canvas*)(this) : nullptr;
//}

} // namespace xpd
