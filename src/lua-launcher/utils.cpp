#include "utils.h"
#include <gfl/utils/options.h>

using namespace Mage;


namespace
{
    const int default_width = 15;
    #define format_print(width) std::cout << "  " << std::left << std::setw(width)

    void trace_special_frame(lua_State *L, int i, bool value_only, int field_count = -1)
    {
        int t = lua_type(L, i);

        if (!value_only)
        {
            if (field_count < 0)
            {
                field_count = lua_gettop(L);
            }

            // frame
            static char buf[128] = { 0 };
            memset(buf, 0, sizeof(buf));
            sprintf(buf, "%d(%d)", i, (i - field_count - 1));
            format_print(default_width) << buf;
            // type
            format_print(default_width) << lua_typename(L, t);
        }

        // value
        switch (t)
        {
        case LUA_TNIL:
            break;
        case LUA_TBOOLEAN:
            format_print(default_width) << (lua_toboolean(L, i) ? "true " : "false ");
            break;
        case LUA_TLIGHTUSERDATA:
            //lua_touserdata(L, i);
            break;
        case LUA_TNUMBER:
            format_print(default_width) << lua_tonumber(L, i);
            break;
        case LUA_TSTRING:
            format_print(default_width) << lua_tostring(L, i);
            break;
        case LUA_TTABLE:
            break;
        case LUA_TFUNCTION:
            //lua_tocfunction(L, i);
            break;
        case LUA_TUSERDATA:
            //lua_topointer(L, i);
            break;
        case LUA_TTHREAD:
            //lua_tothread(L, i);
            break;
        default:
            break;
        } 

        std::cout << std::endl;
    }

    int custom_searcher(lua_State *L)
    {
        std::string module_name;
        module_name.append(Options::Query("script_path").c_str());
        module_name.append(luaL_checkstring(L, 1));
        module_name.append(".lua");

        FILE* file = (FILE*)g_filesys->FileOpen(module_name.c_str(), "rt");
        if (NULL == file)
        {
            return errno;
        }

        char buff[1024] = { 0 };
        g_filesys->FileSeek(file, 0, SEEK_SET);
        size_t readcnt = g_filesys->FileRead(file, buff, sizeof(buff) - 1);
        int ret = luaL_loadbuffer(L, buff, readcnt, module_name.c_str());
        if (ret != LUA_OK)
        {
            return luaL_error(L, "%s", luaL_checkstring(L, -1));
        }

        return 1;//LUA_OK
    }
}

void utils::stack_trace(lua_State* L)
{
    std::cout << "stack info:" << std::endl;

    // titles
    format_print(default_width) << "stack_frame";
    format_print(default_width)  << "field_type";
    format_print(default_width)  << "field_value";
    std::cout << std::endl;

    int top = lua_gettop(L);
    for (int i = top; i > 0; --i)
    {
        trace_special_frame(L, i, false, top);
    }

    std::cout << std::endl;
}

void utils::print_field(lua_State* L, int index)
{
    trace_special_frame(L, index, true);
}

bool utils::add_searcher(lua_State *L)
{
    return add_searcher(L, custom_searcher);
}

bool utils::add_searcher(lua_State *L, lua_CFunction searcher)
{
    lua_getglobal(L, "package");
#if LUA_VERSION_NUM == 501
    lua_getfield(L, -1, "loaders");
#else
    lua_getfield(L, -1, "searchers");
#endif
    lua_remove(L, -2);

    if (!lua_istable(L, -1))
    {
        luaL_error(L, "%s", "can not set searcher");
        return false;
    }

    int num_loaders = 0;
    lua_pushnil(L);
    while (lua_next(L, -2) != 0)
    {
        lua_pop(L, 1);
        ++num_loaders;
    }

    lua_pushinteger(L, num_loaders + 1);
    lua_pushcfunction(L, searcher);
    lua_rawset(L, -3);

    lua_pop(L, 1);

    return true;
}

std::string utils::script_path(const char* path)
{
    std::string temp(Mage::Options::Query("script_path"));
    temp.append(path);
    temp.append(".lua");
    return temp;
}
