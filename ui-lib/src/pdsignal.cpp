#include "m_pd.h"
#include <string.h>

#define DEFSENDVS 64 /* LATER get send to get this from canvas */

/* ----------------------------- send~ ----------------------------- */
static t_class* pdsignal_class;

typedef struct _pdsignal //_sigsend
{
    t_object x_obj;
    t_symbol* x_sym;
    int x_n;
    t_sample* x_vec;
    t_float x_f;

    //receive~
    t_symbol* x_r_sym;
    t_sample* x_r_wherefrom;
    int x_r_n;
} t_pdsignal;

static void* pdsignal_new(t_symbol* s)
{
    t_pdsignal* x = (t_pdsignal*)pd_new(pdsignal_class);
    pd_bind(&x->x_obj.ob_pd, s);

    // TODO different names / binds?

    x->x_sym = s;
    x->x_n = DEFSENDVS;
    x->x_vec = (t_sample*)getbytes(DEFSENDVS * sizeof(t_sample));
    memset((char*)(x->x_vec), 0, DEFSENDVS * sizeof(t_sample));
    x->x_f = 0;
    //
    x->x_r_n = DEFSENDVS; /* LATER find our vector size correctly */
    x->x_r_sym = s;
    x->x_r_wherefrom = 0;
    outlet_new(&x->x_obj, &s_signal);

    return (x);
}

static t_int* pdsignal_perform(t_int* w)
{
    // send
    t_sample* in = (t_sample*)(w[1]);
    t_sample* out = (t_sample*)(w[2]);
    int n = (int)(w[3]);
    while (n--) {
        *out = (PD_BIGORSMALL(*in) ? 0 : *in);
        out++;
        in++;
    }

    //receive

    t_pdsignal* x = (t_pdsignal*)(w[4]);
    //t_sample* out = (t_sample*)(w[1]);
    //int n = (int)(w[3]);
    in = x->x_r_wherefrom;
    n = (int)(w[3]);

    if (in) {
        while (n--)
            *out++ = *in++;
    } else {
        while (n--)
            *out++ = 0;
    }


    return (w + 5);
}

static void pdsignal_set(t_pdsignal* x, t_symbol* s)
{
    t_pdsignal* sender = (t_pdsignal*)pd_findbyclass((x->x_sym = s),
        pdsignal_class);
    if (sender) {
        if (sender->x_n == x->x_n)
            x->x_r_wherefrom = sender->x_vec;
        else {
            pd_error(x, "receive~ %s: vector size mismatch", x->x_sym->s_name);
            x->x_r_wherefrom = 0;
        }
    } else {
        pd_error(x, "receive~ %s: no matching send", x->x_sym->s_name);
        x->x_r_wherefrom = 0;
    }
}

static void pdsignal_dsp(t_pdsignal* x, t_signal** sp)
{
    pdsignal_set(x, x->x_sym);

    if (x->x_n == sp[0]->s_n)
        dsp_add(pdsignal_perform, 4, sp[0]->s_vec, x->x_vec, sp[0]->s_n, x);
    else
        error("sigsend %s: unexpected vector size", x->x_sym->s_name);


    //dsp_add(sigreceive_perform, 3, x, sp[0]->s_vec, sp[0]->s_n);
}

static void pdsignal_free(t_pdsignal* x)
{
    pd_unbind(&x->x_obj.ob_pd, x->x_sym);
    freebytes(x->x_vec, x->x_n * sizeof(t_sample));
}

extern "C" void setup_pdsignal(void)
{
    pdsignal_class = class_new(gensym("pdsignal~"), (t_newmethod)pdsignal_new,
        (t_method)pdsignal_free, sizeof(t_pdsignal), 0, A_DEFSYM, 0);

    CLASS_MAINSIGNALIN(pdsignal_class, t_pdsignal, x_f);

    class_addmethod(pdsignal_class, (t_method)pdsignal_dsp,
        gensym("dsp"), A_CANT, 0);
}




/* ----------------------------- receive~ ----------------------------- */
//static t_class *sigreceive_class;

//typedef struct _sigreceive
//{
//    t_object x_obj;
//    t_symbol *x_sym;
//    t_sample *x_wherefrom;
//    int x_n;
//} t_sigreceive;

//static void *sigreceive_new(t_symbol *s)
//{
//    t_sigreceive *x = (t_sigreceive *)pd_new(sigreceive_class);
//    x->x_n = DEFSENDVS;             /* LATER find our vector size correctly */
//    x->x_sym = s;
//    x->x_wherefrom = 0;
//    outlet_new(&x->x_obj, &s_signal);
//    return (x);
//}

//static t_int* sigreceive_perform(t_int* w)
//{
//    t_sigreceive* x = (t_sigreceive*)(w[1]);
//    t_sample* out = (t_sample*)(w[2]);
//    int n = (int)(w[3]);
//    t_sample* in = x->x_wherefrom;
//    if (in) {
//        while (n--)
//            *out++ = *in++;
//    } else {
//        while (n--)
//            *out++ = 0;
//    }
//    return (w + 4);
//}

// yet removed
/*
/ tb: vectorized receive function /
static t_int *sigreceive_perf8(t_int *w)
{
    t_sigreceive *x = (t_sigreceive *)(w[1]);
    t_sample *out = (t_sample *)(w[2]);
    int n = (int)(w[3]);
    t_sample *in = x->x_wherefrom;
    if (in)
    {
        for (; n; n -= 8, in += 8, out += 8)
        {
            out[0] = in[0]; out[1] = in[1]; out[2] = in[2]; out[3] = in[3];
            out[4] = in[4]; out[5] = in[5]; out[6] = in[6]; out[7] = in[7];
        }
    }
    else
    {
        for (; n; n -= 8, in += 8, out += 8)
        {
            out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
            out[4] = 0; out[5] = 0; out[6] = 0; out[7] = 0;
        }
    }
    return (w+4);
}

*/

//static void sigreceive_dsp(t_sigreceive* x, t_signal** sp)
//{
//    if (sp[0]->s_n != x->x_n) {
//        pd_error(x, "receive~ %s: vector size mismatch", x->x_sym->s_name);
//    } else {
//        sigreceive_set(x, x->x_sym);
//        if (sp[0]->s_n & 7)
//            dsp_add(sigreceive_perform, 3,
//                x, sp[0]->s_vec, sp[0]->s_n);
//        else
//            dsp_add(sigreceive_perf8, 3,
//                x, sp[0]->s_vec, sp[0]->s_n);
//    }
//}

//static void sigreceive_setup(void)
//{
//    sigreceive_class = class_new(gensym("receive~"),
//        (t_newmethod)sigreceive_new, 0,
//        sizeof(t_sigreceive), 0, A_DEFSYM, 0);
//    class_addcreator((t_newmethod)sigreceive_new, gensym("r~"), A_DEFSYM, 0);
//    class_addmethod(sigreceive_class, (t_method)sigreceive_set, gensym("set"),
//        A_SYMBOL, 0);
//    class_addmethod(sigreceive_class, (t_method)sigreceive_dsp,
//        gensym("dsp"), A_CANT, 0);
//    class_sethelpsymbol(sigreceive_class, gensym("send~"));
//}
