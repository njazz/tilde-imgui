#ifndef PDUPDATE_H
#define PDUPDATE_H

#include <ceammc_atomlist.h>
#include <string>

using namespace ceammc;

extern void qtpdUpdate (long objectId, AtomList list);

extern std::string atomListToString(AtomList* list);

#endif // PDUPDATE_H
