---[[
-- loadlib
local entry_mylib = package.loadlib("mylib.dll", "luaopen_mylib")
if entry_mylib then
	local mylib = entry_mylib()
	if not mylib then
		return
	end

	print(mylib.add(1, 2))
else
	print("failed")
end
--]]

--[[
-- require
local entry = require("mylib")
if entry then
	print(entry.add(1, 2))
else
	print("failed")
end
--]]
