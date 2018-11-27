// Lua header files for C++

#ifdef __cplusplus
    #include <lua.hpp>
#else
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
#endif

#include <gfl/gfl.h>
#include <gfl/base/file_sys.h>
#include <gfl/utils/string_util.h>
