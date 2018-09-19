#include <stdlib.h>
#include <stdio.h> 
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

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
	luaL_newlib(L, mylib);
	return 1;
}
