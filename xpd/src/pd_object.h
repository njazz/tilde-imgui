#ifndef PDOBJECT_H
#define PDOBJECT_H

#include "object.h"
#include "pd_arguments.h"
#include "pd_objectobserver.h"

#include "cpd/cpd_canvas.h"

namespace xpd {
class PdCanvas;

/**
 * @brief The PdObject class
 * @details See Object base class
 */
class PdObject : public Object {
    t_cpd_canvas* cnv_;
    t_cpd_object* obj_;
    size_t inlet_n_;
    size_t outlet_n_;
    PdArguments args_;
    std::shared_ptr<PdObjectObserver> observer_;

public:
    PdObject(const Canvas* parent, const std::string& name, const PdArguments& args = PdArguments(), int x = 0, int y = 0);
    ~PdObject();

    void setX(int x) override;
    void setY(int y) override;

    size_t inletCount() const override;
    size_t outletCount() const override;

    virtual size_t childrenCount() const override;

    const Arguments& arguments() const override;

    t_cpd_object* pdObject();

    virtual ObjectType type() const override;

    void sendBang() override;
    void sendFloat(float f) override;
    void sendSymbol(const std::string& s) override;
    void sendList(const Arguments a) override;
    void sendStringAsList(std::string s);

    void setReceiveSymbol(const std::string& s);

    virtual void registerObserver(ObserverPtr o) override;
    virtual void deleteObserver(ObserverPtr) override;

    // subpatches prototype
    PdCanvas* asPdCanvas();

    //virtual Canvas* asCanvas() const override;
    //virtual ObjectId createObject(const std::string& name, int x, int y) override;
};

} // namespace xpd

#endif // PDOBJECT_H
