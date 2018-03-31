#include "cpd_connection.h"
#include "cpd_canvas.h"
#include "cpd_object.h"
#include "pr_log.h"

#include "m_pd.h"
extern "C" {
#include "m_imp.h"
}

typedef struct _cpd_connection {
    t_cpd_object* src;
    t_cpd_object* dest;
    t_cpd_connection* next;
    size_t src_outlet;
    size_t dest_inlet;
    t_cpd_conn_type type;

} t_cpd_connection;

static t_cpd_connection* cpd_connection_list_new()
{
    auto res = new t_cpd_connection;
    res->src = 0;
    res->dest = 0;
    res->next = 0;
    res->dest_inlet = 0;
    res->src_outlet = 0;
    return res;
}

void cpd_connection_list_free(t_cpd_connection* lst)
{
    while (lst) {
        auto next = lst->next;
        delete lst;
        lst = next;
    }
}

size_t cpd_connection_count(t_cpd_connection* lst)
{
    size_t n = 0;

    while (lst) {
        lst = lst->next;
        n++;
    }

    return n;
}

t_cpd_connection* cpd_connection_next(t_cpd_connection* lst)
{
    return lst ? lst->next : nullptr;
}

t_cpd_object* cpd_connection_source(t_cpd_connection* c)
{
    return c ? c->src : nullptr;
}

t_cpd_object* cpd_connection_destination(t_cpd_connection* c)
{
    return c ? c->dest : nullptr;
}

size_t cpd_connection_source_outlet(t_cpd_connection* c)
{
    return c ? c->src_outlet : 0;
}

size_t cpd_connection_destination_inlet(t_cpd_connection* c)
{
    return c ? c->dest_inlet : 0;
}

t_cpd_connection* cpd_canvas_connections(t_cpd_canvas* cnv)
{
    if (!cnv) {
        DEBUG("NULL given");
        return nullptr;
    }

    auto src_object = cpd_canvas_first_object(cnv);
    if (!src_object)
        return nullptr;

    t_cpd_connection* lst = nullptr;

    while (src_object) {
        auto obj_conn = cpd_object_out_connections(src_object);

        if (obj_conn)
            lst = cpd_connection_append(obj_conn, lst);

        src_object = cpd_object_next(src_object);
    }

    return lst;
}

t_cpd_conn_type cpd_connection_type(t_cpd_connection* c)
{
    return c ? c->type : CPD_CONNECTION_CONTROL;
}

t_cpd_connection* cpd_object_out_connections(t_cpd_object* obj)
{
    t_cpd_connection* res = nullptr;

    size_t n = cpd_object_outlet_count(obj);
    while (n > 0) {
        n--;
        t_outlet* src_outlet = nullptr;
        const int src_outlet_no = n;
        auto pd_conn = obj_starttraverseoutlet(obj, &src_outlet, src_outlet_no);
        while (pd_conn) {
            t_object* dest_object = nullptr;
            t_inlet* dest_inlet = nullptr;
            int dest_inlet_no = 0;
            pd_conn = obj_nexttraverseoutlet(pd_conn, &dest_object, &dest_inlet, &dest_inlet_no);

            t_cpd_connection* conn = cpd_connection_list_new();
            conn->src = obj;
            conn->dest = dest_object;
            conn->src_outlet = src_outlet_no;
            conn->dest_inlet = dest_inlet_no;

            conn->type = obj_issignaloutlet(obj, src_outlet_no) ? CPD_CONNECTION_SIGNAL : CPD_CONNECTION_CONTROL;

            if (!res) {
                res = conn;
            } else {
                conn->next = res;
                res = conn;
            }
        }
    }

    return res;
}

t_cpd_connection* cpd_connection_last(t_cpd_connection* c)
{
    while (c) {
        if (c->next == nullptr)
            return c;

        c = c->next;
    }

    return nullptr;
}

t_cpd_connection* cpd_connection_append(t_cpd_connection* c0, t_cpd_connection* c1)
{
    auto last = cpd_connection_last(c0);
    if (!last)
        return c1;

    last->next = c1;
    return c0;
}
