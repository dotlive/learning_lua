#ifndef _LAUNCHER_UTILS_H_
#define _LAUNCHER_UTILS_H_

#include <iomanip>
#include <iostream>
#include "pch.h"

class utils
{
public:
    static void stack_trace(lua_State *L);
    static void print_field(lua_State *L, int index);
};

#define trace_debug(trace_all) { if (trace_all) utils::stack_trace(L); else utils::print_field(L, -1); }

#endif // _LAUNCHER_UTILS_H_
