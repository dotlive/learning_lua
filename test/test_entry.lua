-- setup environment
require("common")
local lu = require("luaunit")

local function add(a, b)
	return a + b
end

function testAdd(...)
	lu.assertEquals(add(1, 3), 4)
end

os.exit(lu.LuaUnit.run(), true)
--]]
