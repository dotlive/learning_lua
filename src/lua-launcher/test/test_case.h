#include "../utils.h"

//////////////////////////////////////////////////////////////////////////
// lua stack operation

inline void test_luastack()
{
    lua_State *L = luaL_newstate();

    // c -> stack
    lua_pushstring(L, "hello world");
    lua_pushnumber(L, 10);

    utils::stack_trace(L);

    // stack -> c
    if (lua_isnumber(L, -1))
    {
        std::cout << lua_tonumber(L, -1) << std::endl;
    }
    if (lua_isstring(L, -2))
    {
        std::cout << lua_tostring(L, -2) << std::endl;
    }

    lua_close(L);
}

//////////////////////////////////////////////////////////////////////////
// c++ call lua

#define TEST_LOADFILE 0
inline void test_cppcalllua()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

#if TEST_LOADFILE
    int ret = luaL_loadfile(L, "cppcalllua.lua");
    if (ret != LUA_OK)
    {
        std::cout << "read lua file error!" << std::endl;
        return;
    }

    ret = lua_pcall(L, 0, 0, 0);
    if (ret != LUA_OK)
    {
        std::cout << "run script error!" << std::endl;
        return;
    }
#else
    // luaL_dofile = luaL_loadfile + lua_pcall
    int ret = luaL_dofile(L, "../lua-launcher/test/cppcalllua.lua");
    if (ret != LUA_OK)
    {
        std::cout << "do lua file error!" << std::endl;
        return;
    }
#endif

    bool trace_stack = true;

    // lua -> stack
    lua_getglobal(L, "name");
    trace_debug(trace_stack);
    lua_getglobal(L, "version");
    trace_debug(trace_stack);

    lua_getglobal(L, "info");
    trace_debug(trace_stack);
    {
        // access table field
        lua_getfield(L, -1, "name");
        trace_debug(false);
        lua_getfield(L, -2, "gender");
        trace_debug(false);

        // modify table field
        lua_pushstring(L, "007");
        trace_debug(true);
        lua_setfield(L, -4, "name");    // -4: table's index; 1st. table[name] = "007", 2nd. pop 007 from the stack
        trace_debug(true);

        // check new name
        lua_getfield(L, -3, "name");
        trace_debug(true);
    }

    lua_getglobal(L, "sum");
    trace_debug(trace_stack);
    {
        // call lua function
        lua_pushnumber(L, 1);
        lua_pushnumber(L, 2);
        lua_pcall(L, 2, 1, 0);
        trace_debug(false);
    }

    trace_debug(true);

    lua_close(L);
}

//////////////////////////////////////////////////////////////////////////
// lua call c++

int sub(lua_State *L)
{
    // stack -> c
    int a = (int)luaL_checknumber(L, 1);
    int b = (int)luaL_checknumber(L, 2);
    // c -> stack
    lua_pushnumber(L, a - b);
    return 1;
}

inline void test_luacallcpp()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "sub", sub);

    int ret = luaL_dofile(L, "../lua-launcher/test/luacallcpp.lua");
    if (ret != LUA_OK)
    {
        std::cout << "read lua file error!" << std::endl;
        return;
    }

    lua_close(L);
}
