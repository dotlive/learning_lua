# Lua 学习笔记

## 参考链接

[LuaSource](http://lua-users.org/wiki/LuaSource)

## 命名风格

- 内部模块的 API

	Lua 内部模块的 API， 以 **luaX_xxx** 风格命名：大写字母表识**内部模块名**；小写字母描述**方法名**。整理如下：

	| 前缀 | 所在文件 | 前缀说明 |
	| --- | --- | --- |
	| luaA_ | lapi.c
	| luaB_ | lbaselib.c
	| luaC_ | lgc.c | Collection
	| luaD_ | ldo.c | Do
	| luaE_ | lstate.c
	| luaF_ | lfunc.c | Function
	| luaG_ | ldebug.c
	| luaH_ | ltable.c | Hash
	| luaI_ | lauxlib.c
	| luaK_ | lcode.c
	| luaL_ | lauxlib.c/h, linit.c | public functions
	| luaM_ | lmem.c | Memory
	| luaO_ | lobject.c | Object
	| luaP_ | lopcodes.c
	| luaS_ | lstring.c | String
	| luaT_ | ltm.c | Tag
	| luaX_ | llex.c
	| luaU_ | ldump.c, lundump.c
	| luaV_ | lvm.c | Virtual
	| luaX_ | llex.c
	| luaY_ | lparser.c | Yacc
	| luaZ_ | lzio.c
	| lua_  | lapi.c/h + luaconfig.h, debug.c
	| luai_ | luaconf.h
	| luaopen_ | luaconf.h + libraries (lbaselib.c, ldblib.c, liolib.c, lmathlib.c, loadlib.c, loslib.c, lstrlib.c, ltablib.c)

-  给外部程序使用的 API

	提供给外部程序使用的 API，以 **lua_xxx** 风格命名，定义在 lua.h 文件中。主要分为以下几部分：

	- state 操作相关
	```
	lua_newstate
	lua_close
	lua_newthread
	lua_atpanic
	lua_version
	```

	- stack 操作相关
	```
	lua_absindex
	lua_gettop
	lua_settop
	lua_pushvalue
	lua_remove
	lua_insert
	lua_replace
	lua_copy
	lua_checkstack
	lua_xmove
	```
	- access functions (stack -> c)	// lua_toXXX
	```
	lua_isnumber
	lua_isstring
	lua_iscfunction
	lua_isuserdata
	lua_type
	lua_typename

	lua_tonumberx
	lua_tointegerx
	lua_tounsignedx
	lua_toboolean
	lua_tolstring
	lua_rawlen
	lua_tocfunction
	lua_touserdata
	lua_tothread
	lua_topointer
	```

	- push functions (c -> stack; lua_pushXXX)
	```
	lua_pushnil
	lua_pushnumber
	lua_pushinteger
	lua_pushsigned
	lua_pushlstring
	lua_pushstring
	lua_pushvfstring
	lua_pushfstring
	lua_pushcclosure
	lua_pushboolean
	lua_pushlightuserdata
	lua_pushthread
	```

	- get functions (lua -> stack; lua_getXXX / lua_rawgetXXX)
	```
	lua_getglobal
	lua_gettable
	lua_getfield
	lua_rawget
	lua_rawgeti
	lua_rawgetp
	lua_createtable
	lua_newuserdata
	lua_getmetatable
	lua_getuservalue
	```
	
	- set function (stack -> lua; lua_setXXX / lua_rawsetXXX)
	```
	lua_setglobal
	lua_settable
	lua_setfield
	lua_rawset
	lua_rawseti
	lua_rawsetp
	lua_setmetatable
	lua_setuservalue
	```

	- load & call functions (load and run lua code)
	```
	lua_callk
	lua_getctx
	lua_pcallk
	lua_load
	lua_dump
	```

	- coroutine 操作相关
	```
	lua_yieldk
	lua_resume
	lua_status
	```

	- gc 相关
	```
	lua_gc
	```

	- debug 相关
	```
	lua_getstack
	lua_getinfo
	lua_getlocal
	lua_setlocal
	lua_getupvalue
	lua_setupvalue
	lua_upvalueid
	lua_upvaluejoin
	lua_sethook
	lua_gethook
	lua_gethookmask
	lua_gethookcount
	```

	- miscellaneous functions
	```
	lua_error
	lua_next
	lua_concat
	lua_len
	lua_getallocf
	lua_setallocf
	```

- 给库开发用的 API

	提供给库开发用的 API，使用 **luaL_xxx** 风格命名，定义在 lauxlib.h 文件中。全部使用了 lua.h 中定义的 API，没有使用一个内部 API，所以 luaL_XXX 是对 lua_XXX 的进一步封装。
	```
	luaL_checkversion_		// luaL_checkversion
	luaL_getmetafield
	luaL_callmeta
	luaL_tolstring
	luaL_argerror

	// optXXX 比 checkXXX 多了一个默认值参数
	luaL_checklstring
	luaL_optlstring
	luaL_checknumber
	luaL_optnumber
	luaL_checkinteger
	luaL_optinteger
	luaL_checkunsigned
	luaL_optunsigned

	luaL_checkstack
	luaL_checktype
	luaL_checkany

	luaL_newmetatable
	luaL_setmetatable
	luaL_testudata
	luaL_checkudata

	luaL_where
	luaL_error

	luaL_checkoption
	luaL_fileresult
	luaL_execresult

	luaL_ref
	luaL_unref

	luaL_loadfilex			// luaL_loadfile
	luaL_loadbufferx
	luaL_loadstring
	luaL_newstate

	luaL_len
	luaL_gsub
	luaL_setfuncs
	luaL_getsubtable
	luaL_traceback

	luaL_requiref

	// buffer 操作相关
	luaL_buffinit
	luaL_prepbuffsize		// luaL_prepbuffer
	luaL_addlstring
	luaL_addstring
	luaL_addvalue
	luaL_pushresult
	luaL_pushresultsize
	luaL_buffinitsize
	```

## 习惯相关

- lua 处理偏移量时，习惯用负数表示从尾部倒数。对栈的索引就是如此，字符串的索引也遵循同一规则
```
    1. 对栈索引来说，如果为负数的话，top为-1；为正数的话，第一个压入栈的元素索引为1。如：
如果堆栈有 n 个元素，那么索引 1 表示第一个元素（也就是最先被压入堆栈的元素）而索引 n 则指最后一个元素；索引 -1 也是指最后一个元素（即栈顶的元素），索引 -n 是指第一个元素。如果索引在 1 到栈顶之间（也就是，1 ≤ abs(index) ≤ top）我们就说这是个有效的索引。

    注：此处可以参考python中的索引处理；换句话，负索引，可以理解为"从后向前数(倒数)"。
```

- 当一个代码块 (chunk) 被加载的时候，默认的 _ENV 就是当前的全局表 (_G)
