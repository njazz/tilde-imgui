#include "cpd_receiver.h"
#include "cpd_list.h"
#include "cpd_object.h"
#include "pr_log.h"

#include "m_pd.h"
extern "C" {
#include "m_imp.h"
}

static const char* RECEIVER_CLASS_NAME = "@receiver object@";

typedef struct _receiver {
    t_object x_obj;
    t_cpd_receiver_callback callback;
} t_receiver;

static t_class* receiver_class = 0;

CPD_EXTERN t_cpd_object* cpd_receiver_new()
{
    t_receiver* x = reinterpret_cast<t_receiver*>(pd_new(receiver_class));
    x->callback = 0;
    return reinterpret_cast<t_cpd_object*>(x);
}

CPD_EXTERN void cpd_receiver_free(t_receiver* x)
{

}

static void cpd_receiver_any(t_receiver* x, t_symbol* sel, int argc, t_atom* argv)
{
    if (!x->callback)
        return;

    t_cpd_list* msg = cpd_list_new(0);
    cpd_list_append_symbol(msg, sel);

    for (int i = 0; i < argc; i++)
        cpd_list_append(msg, &argv[i]);

    //callback
    (x->callback)(msg);

    cpd_list_free(msg);
}

CPD_EXTERN void cpd_receiver_set_callback(t_receiver* x,t_cpd_receiver_callback c)
{
    x->callback = c;
}

CPD_EXTERN void cpd_receiver_init()
{
    // already initialized
    if (receiver_class)
        return;

    receiver_class = class_new(gensym(RECEIVER_CLASS_NAME),
        reinterpret_cast<t_newmethod>(cpd_receiver_new),
        reinterpret_cast<t_method>(cpd_receiver_free),
        sizeof(t_receiver), 0, A_NULL);

    class_addanything(receiver_class, reinterpret_cast<t_method>(cpd_receiver_any));
}


