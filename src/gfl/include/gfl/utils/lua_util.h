#ifndef _LAUNCHER_UTILS_H_
#define _LAUNCHER_UTILS_H_

#include <iomanip>
#include <iostream>
#include <string>
#include <lua.hpp>

namespace Mage
{
    class LuaUtil
    {
    public:
        static void print_stack(lua_State *L);
        static void print_field(lua_State *L, int index);

        static bool add_searcher(lua_State *L);
        static bool add_searcher(lua_State *L, lua_CFunction searcher);

        static std::string script_path(const char* path);
    };

    #define trace_debug(trace_all) { if (trace_all) LuaUtil::print_stack(L); else LuaUtil::print_field(L, -1); }
}

#endif // _LAUNCHER_UTILS_H_
