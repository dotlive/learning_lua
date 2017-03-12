print("==>test dofile(compile once, run once):")
dofile("util.lua")
dofile("util.lua")

print("==>test require(compile once, run many times):")
require("util")
require("util")

print("==>test loadfile(compile only -- from file):")
loadfile("util.lua")

print("==>test loadstring(compile only -- from string):")
f = loadstring("local i = 20; return i + 10")
--print(f())
