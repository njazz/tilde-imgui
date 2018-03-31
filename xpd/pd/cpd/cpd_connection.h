#ifndef CPD_CONNECTION_H
#define CPD_CONNECTION_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

CPD_EXTERN t_cpd_connection* cpd_canvas_connections(t_cpd_canvas* cnv);
CPD_EXTERN t_cpd_connection* cpd_object_out_connections(t_cpd_object* obj);
CPD_EXTERN void cpd_connection_list_free(t_cpd_connection* lst);
CPD_EXTERN size_t cpd_connection_count(t_cpd_connection* lst);
CPD_EXTERN t_cpd_connection* cpd_connection_next(t_cpd_connection* lst);
CPD_EXTERN t_cpd_object* cpd_connection_source(t_cpd_connection* c);
CPD_EXTERN t_cpd_object* cpd_connection_destination(t_cpd_connection* c);
CPD_EXTERN size_t cpd_connection_source_outlet(t_cpd_connection* c);
CPD_EXTERN size_t cpd_connection_destination_inlet(t_cpd_connection* c);
CPD_EXTERN t_cpd_conn_type cpd_connection_type(t_cpd_connection* c);

CPD_EXTERN t_cpd_connection* cpd_connection_last(t_cpd_connection* c);
CPD_EXTERN t_cpd_connection* cpd_connection_append(t_cpd_connection* c0, t_cpd_connection* c1);

#ifdef __cplusplus
}
#endif

#endif // CPD_CONNECTION_H
