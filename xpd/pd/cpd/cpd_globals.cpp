#include "cpd_globals.h"

#include "m_pd.h"

t_cpd_symbol* CPD_SYMBOL_PD = 0;
t_cpd_symbol* CPD_SYMBOL_OBJ = 0;
t_cpd_symbol* CPD_SYMBOL_DSP = 0;
t_cpd_symbol* CPD_SYMBOL_EMPTY = 0;
t_cpd_symbol* CPD_SYMBOL_TEMPLATE_ARRAY = 0;
t_cpd_symbol* CPD_SYMBOL_ARRAY_LINEWIDTH = 0;
t_cpd_symbol* CPD_SYMBOL_ARRAY_STYLE = 0;

void cpd_globals_init()
{
    CPD_SYMBOL_PD = gensym("pd");
    CPD_SYMBOL_OBJ = gensym("obj");
    CPD_SYMBOL_DSP = gensym("dsp");
    CPD_SYMBOL_EMPTY = gensym("");

    // internal
    CPD_SYMBOL_TEMPLATE_ARRAY = gensym("pd-float-array");
    CPD_SYMBOL_ARRAY_LINEWIDTH = gensym("linewidth");
    CPD_SYMBOL_ARRAY_STYLE = gensym("style");
}
