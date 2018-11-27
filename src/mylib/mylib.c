/*
    for macosx:
        https://blog.csdn.net/xenyinzen/article/details/4491338
*/

#ifdef __cplusplus
    #include <lua.hpp>
#else
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
#endif


static int lua_add(lua_State *L)
{
	double a = luaL_checknumber(L, 1);
	double b = luaL_checknumber(L, 2);

	lua_pushnumber(L, a + b);

	return 1;
}

static const struct luaL_Reg mylib[] = 
{
	{"add",		lua_add},
	{NULL,		NULL}
};

LUALIB_API int luaopen_mylib(lua_State *L)
{
#if LUA_VERSION_NUM > 501
    luaL_newlib(L, mylib);
#else
	luaL_register(L, "mylib", mylib);
#endif
	return 1;
}
