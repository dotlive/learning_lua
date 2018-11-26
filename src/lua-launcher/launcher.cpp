#include <lua.h>
#include <lauxlib.h>
#include <iostream>

int main(int argc, char** argv)
{
    lua_State* L = luaL_newstate();
    // 将hello world 压入虚拟栈
    lua_pushstring(L, "hello world");
    // 将整数10压入虚拟栈
    lua_pushnumber(L, 10);
    if (lua_isnumber(L, -1) && lua_isstring(L, -2))
    {
        // 从虚拟栈中取出对应位置的元素
        int num = lua_tonumber(L, -1);
        const char* str = lua_tostring(L, -2);
        printf("%d %s \n", num, str);
    }
    lua_close(L);

    system("pause");
    return 0;
}
