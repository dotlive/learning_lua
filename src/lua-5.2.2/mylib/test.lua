---[[
-- loadlib
local entry_pb = package.loadlib("lpblib.dll", "luaopen_pb")
if entry_pb then
	local pb = entry_pb()
	if not pb then
		return
	end

	print("success")

else
	print("failed")
end
--]]

---[[
-- require
local entry = require("mylib")
if entry then
	print(entry.add(1, 2))
else
	print("failed")
end
--]]
