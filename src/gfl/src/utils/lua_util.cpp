#include <gfl/gfl.h>
#include <gfl/utils/lua_util.h>
#include <gfl/utils/options.h>
#include <gfl/utils/string_util.h>

using namespace Mage;


namespace
{
    //////////////////////////////////////////////////////////////////////////

    static void print_item(lua_State *L, int i, int as_key);

    static int is_identifier(const char *s)
    {
        while (*s)
        {
            if (!isalnum(*s) && *s != '_') return 0;
            ++s;
        }
        return 1;
    }

    static int is_seq(lua_State *L, int i)
    {
        int keynum = 1;
        lua_pushnil(L);
        while (lua_next(L, i))
        {
            lua_rawgeti(L, i, keynum);
            if (lua_isnil(L, -1))
            {
                lua_pop(L, 3);
                return 0;
            }
            lua_pop(L, 2);
            keynum++;
        }
        return 1;
    }

    static void print_seq(lua_State *L, int i)
    {
        std::cout << "{";

        for (int k = 1;; ++k)
        {
            lua_rawgeti(L, i, k);
            if (lua_isnil(L, -1)) break;
            if (k > 1) printf(", ");
            print_item(L, -1, 0);
            lua_pop(L, 1);
        }
        lua_pop(L, 1);

        std::cout << "}";
    }

    static void print_table(lua_State *L, int i)
    {
        if (i < 0) i = lua_gettop(L) + i + 1;

        if (is_seq(L, i))
        {
            print_seq(L, i);
        }
        else
        {
            const char *prefix = "{";
            lua_pushnil(L);
            while (lua_next(L, i))
            {
                printf("%s", prefix);
                print_item(L, -2, 1);   // key
                printf(" = ");
                print_item(L, -1, 0);   // value
                lua_pop(L, 1);
                prefix = ", ";
            }
            printf("}");
        }
    }

    static char *get_fn_string(lua_State *L, int i)
    {
        static char fn_name[1024];

        if (i < 0) i = lua_gettop(L) + i + 1;

        lua_getglobal(L, "_G");
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            if (lua_rawequal(L, i, -1))
            {
                snprintf(fn_name, 1024, "function:%s", lua_tostring(L, -2));
                lua_pop(L, 3);
                return fn_name;
            }
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
        snprintf(fn_name, 1024, "function:%p", lua_topointer(L, i));
        return fn_name;
    }

    static void print_item(lua_State *L, int i, int as_key)
    {
        int ltype = lua_type(L, i);
        const char *first = (as_key ? "[" : "");
        const char *last = (as_key ? "]" : "");

        static char buff[512];
        memset(buff, 0, sizeof(buff));

        switch (ltype)
        {
        case LUA_TNIL:
            // This can't be a key, so we can ignore as_key here.
            if (!as_key)
            {
                printf("nil");
            }
            break;

        case LUA_TBOOLEAN:
            printf("%s%s%s", first, lua_toboolean(L, i) ? "true" : "false", last);
            break;

        case LUA_TNUMBER:
            printf("%s%g%s", first, lua_tonumber(L, i), last);
            break;

        case LUA_TSTRING:
        {
            const char *s = lua_tostring(L, i);
            if (is_identifier(s) && as_key)
            {
                printf("%s", s);
            }
            else
            {
                printf("%s'%s'%s", first, s, last);
            }
        }
        break;

        case LUA_TTABLE:
        {
            printf("%s", first);
            print_table(L, i);
            printf("%s", last);
        }
        return;

        case LUA_TFUNCTION:
            printf("%s%s%s", first, get_fn_string(L, i), last);
            break;

        case LUA_TUSERDATA:
        case LUA_TLIGHTUSERDATA:
            printf("%suserdata:%p%s", first, lua_topointer(L, i), last);
            break;

        case LUA_TTHREAD:
            printf("%sthread:", first, lua_topointer(L, i), last);
            break;

        default:
            printf("<internal_error_in_print_stack_item!>");
            break;
        }
    }

    //////////////////////////////////////////////////////////////////////////

    int custom_searcher(lua_State *L)
    {
        std::string module_name = luaL_checkstring(L, 1);

        // replace split from '.' to '/'
        std::string final_path;
        if (std::string::npos != module_name.find("."))
        {
            std::vector<std::string> sub_dirs;
            StringUtil::Split(sub_dirs, module_name, ".");

            if (sub_dirs.size() > 1)
            {
                size_t max_index = sub_dirs.size() - 1;
                for (size_t idx = 0; idx < max_index; ++idx)
                {
                    if (sub_dirs[idx].empty())
                    {
                        continue;
                    }

                    final_path += sub_dirs[idx];
                    final_path += "/";
                }

                final_path += sub_dirs[max_index];
            }
        }
        else
        {
            final_path = module_name;
        }

        module_name = LuaUtil::script_path(final_path.c_str());
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

namespace Mage
{
    void LuaUtil::print_stack(lua_State* L)
    {
        printf("stack info:\n");

        int top = lua_gettop(L);
        if (top <= 0)
        {
            printf("<empty>");
        }
        else
        {
            for (int i = top; i > 0; --i)
            {
                // frame
                printf("  [%-2d %2d] ", i, (i - top - 1));
                // type
                int t = lua_type(L, i);
                printf("  %-8s ", lua_typename(L, t));
                // value
                print_item(L, i, 0);
                printf("\n");
            }
        }

        printf("\n");
    }

    void LuaUtil::print_field(lua_State* L, int index)
    {
        print_item(L, index, 0);
        printf("\n");
    }

    bool LuaUtil::add_searcher(lua_State *L)
    {
        return add_searcher(L, custom_searcher);
    }

    bool LuaUtil::add_searcher(lua_State *L, lua_CFunction searcher)
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

    std::string LuaUtil::script_path(const char* path)
    {
        std::string temp(Mage::Options::Query("script_path"));
        temp.append(path);
        temp.append(".lua");
        return temp;
    }
}
