package.path = package.path .. ";../utils/?.lua"
package.cpath = package.cpath .. ";../../src/bin/?.dll"

local lu = require("luaunit")

-- 不会去匹配 cpath
local load_by_loadlib = function(libname, entryfunc)
	local entry = package.loadlib(libname, entryfunc)
	if not entry then
		return nil
	end
	return entry()
end

local load_by_require = function(libname)
	local entry = require(libname)
	if not entry then
		return nil
	end
	return entry
end

function testAdd(...)
	local mylib = load_by_loadlib("../mylib.dll", "luaopen_mylib")
	if mylib then
		print("1")
		lu.assertEquals(mylib.add(1, 2), 3)
	else
		print("11")
	end
end

function testAdd2(...)
	local mylib2 = load_by_require("mylib")
	if mylib2 then
		print("2")
		lu.assertEquals(mylib2.add(2, 3), 5)
	else
		print("22")
	end
end

os.exit(lu.LuaUnit.run(), true)


