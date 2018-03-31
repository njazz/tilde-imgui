#include "cpd_system_lists.h"
extern "C"{
#include "m_pd.h"
#include "m_imp.h"
#include "s_stuff.h"
}


std::string cpd_system_list_bind_objects()
{
    std::string ret = "";
    /*
     * needs x_ceammc.h / .c to run

    
    t_symbol** hashTable = pd_ceammc_gensym_hash_table();
    
    if (!hashTable) {
        error("hash table error!");
        return "";
    }
    
    for (int i = 0; i < pd_ceammc_gensym_hash_table_size(); i++) {
        t_symbol* s = hashTable[i];
        
        if (s) {
            if (s->s_thing) {
                ret += string(s->s_name) + ",";
            }
        }
    }
    */
    return ret;
}

std::vector<std::string> cpd_system_list_loaded_classes()
{

    std::vector<std::string> ret;

    /*
     * needs x_ceammc.h / .c to run
    
    // TODO
    
    t_loaded_classes_list* list = sys_loaded_classes;
    
    int fuse = 10000;
    while (list && fuse) {
        ret.push_back( string(list->ll_name->s_name) );
        list = list->ll_next;
        fuse--;
    }

    */

    return ret;
}
