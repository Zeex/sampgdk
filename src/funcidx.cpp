// Some popular SA:MP scripts/includes use funcidx() to hook callbacks, etc.
// Since we hook amx_FindPublic to force it always return AMX_ERR_NONE, 
// the funcidx() function have become bugged and doesn't return -1 anymore
// but AMX_EXEC_GDK (which is not -1).
// So we provide our own implementation of funcidx which takes that fact into account.
// Thanks to Incognito for finding this bug.

#include <sampgdk/sampgdk.h>

#include "amxapihooks.h"

// native funcidx(const funcname[]);
cell AMX_NATIVE_CALL funcidx(AMX *amx, cell *params) {
    char *funcname;
    amx_StrParam(amx, params[1], funcname);
    int index;
    int error = amx_FindPublic(amx, funcname, &index);
    if (error != AMX_ERR_NONE || (error == AMX_ERR_NONE && index == AMX_EXEC_GDK)) {
        return -1;
    }
    return index;
}

