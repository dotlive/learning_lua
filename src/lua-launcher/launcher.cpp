#include <gfl/utils/options.h>

#define DEBUG_MODE 1

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

    system("pause");
    return 0;
}

#else

#include "utils.h"

int main(int argc, char* argv[])
{
    Mage::Options::Load("../res/config.xml");

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    utils::add_searcher(L);

    std::string init_path = Mage::Options::Query("script_path") + "init.lua";
    if (LUA_OK != luaL_dofile(L, init_path.c_str()))
    {
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

    return 0;
}

#endif
