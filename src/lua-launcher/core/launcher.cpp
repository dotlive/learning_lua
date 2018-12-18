//#include <gfl/utils/options.h>
//#include <gfl/utils/lua_util.h>

#include "custom_allocator.h"
#include <stdlib.h>
#include <time.h>

//using namespace Mage;

#define DEBUG_MODE 0

#if DEBUG_MODE
#include "test/test_case.h"

int main(int argc, char* argv[])
{
    Mage::Options::Load("../res/config.xml");

    std::cout << "test_luastack---------------------------------------" << std::endl;
    test_luastack();
    std::cout << "test_cppcalllua-------------------------------------" << std::endl;
    test_cppcalllua();
    std::cout << "test_luacallcpp-------------------------------------" << std::endl;
    test_luacallcpp();
    std::cout << "test_customsearcher---------------------------------" << std::endl;
    test_customsearcher();
    std::cout << "test_setglobalvalue---------------------------------" << std::endl;
    test_setglobalvalue();

    system("pause");
    return 0;
}

#else

int main(int argc, char* argv[])
{
    /*
    Mage::Options::Load("../res/config.xml");

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    LuaUtil::add_searcher(L);

    if (LUA_OK != luaL_dofile(L, LuaUtil::script_path("init").c_str()))
    {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        system("pause");
        return 0;
    }

    char buff[256];
    while (fgets(buff, sizeof(buff), stdin) != NULL)
    {
        int ret = luaL_loadbuffer(L, buff, strlen(buff), "stdin") || lua_pcall(L, 0, 0, 0);
        if (ret != LUA_OK)
        {
            fprintf(stderr, "%s", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }

    lua_close(L);

    system("pause");*/

    srand((int)time(0));

    int COUNT = 10000;
    int MAX_SIZE = 1024;

    custom_allocator ca;
    for (int idx = 0; idx < COUNT; ++idx)
    {
        int size = rand() % MAX_SIZE + 1;
        ca.alloc(size);
    }

    return 0;
}

#endif
