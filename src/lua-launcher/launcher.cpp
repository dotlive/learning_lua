#include <iostream>

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

// from top to base
static void stack_trace(lua_State* L)
{
    std::cout << "begin dump lua stack" << std::endl;
    int top = lua_gettop(L);
    for (int i = top; i > 0; --i)
    {
        int t = lua_type(L, i);
        std::cout << i << " " << lua_typename(L, t) << " ";

        switch (t)
        {
            case LUA_TSTRING:
            {
                std::cout << lua_tostring(L, i) << std::endl;
            }
            break;
            case LUA_TBOOLEAN:
            {
                std::cout << (lua_toboolean(L, i) ? "true " : "false ") << std::endl;
            }
            break;
            case LUA_TNUMBER:
            {
                std::cout << lua_tonumber(L, i) << std::endl;
            }
            break;
            default:
            {
                std::cout << lua_typename(L, t) << std::endl;
            }
            break;
        }
    }
    std::cout << "end dump lua stack" << std::endl << std::endl;
}

int main(int argc, char* argv[])
{
    lua_State *L = luaL_newstate();

    // to stack
    lua_pushstring(L, "hello world");
    lua_pushnumber(L, 10);

    stack_trace(L);

    // from stack
    if (lua_isnumber(L, -1))
    {
        std::cout << lua_tonumber(L, -1) << std::endl;
    }
    if (lua_isstring(L, -2))
    {
        std::cout << lua_tostring(L, -2) << std::endl;
    }

    lua_close(L);

    system("pause");
    return 0;
}
