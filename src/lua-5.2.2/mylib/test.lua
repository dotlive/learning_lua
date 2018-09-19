---[[
-- loadlib
local entry = package.loadlib("mylib.dll", "luaopen_mylib")
if entry then
	entry()
	print(entry().add(1,2))
else
	print("failed")
end
--]]

--[[
-- require
local entry = require("mylib")
if entry then
	print(entry.add(1,2))
else
	print("failed")
end
--]]
