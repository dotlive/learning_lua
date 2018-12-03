--print("hello")

for i, v in pairs(_G) do
    print("name:", i, ", type:", type(v))
end

print(_G)
print(_ENV)

local old_print = print
local old_load = load
local old_pairs = pairs

local _tenv = {}
_tenv.tprint = print
_tenv.tpairs = pairs

old_print(_ENV)
old_print(_ENV._G)
old_print(_G)

local _tg = _G
_G = {}
_ENV = _tenv
x = 1

for i, _ in tpairs(_ENV) do
    tprint(i)
end

old_print(_ENV)
old_print(_G)

local a = old_load("y = 1; for i, v in tpairs(_ENV) do tprint(i); end", "test", "t", _tenv)
a();