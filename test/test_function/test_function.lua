--function as table's field

lib = {}
lib.foo = function(a, b) return a + b end
lib.goo = function(a, b) return a - b end
print(lib.foo(1, 2))
print(lib.goo(3, 4))


lib2 = 
{
	foo = function(a, b)
		return a * b
	end
}
print(lib2.foo(2, 3))



print("========================================")



-- iterator

function list_iter(t)
	local idx = 0
	local max = table.getn(t)
	return function()
		idx = idx + 1
		if idx <= max then 
			return t[idx]
		end
	end
end

local tbl = {1, 2, 3, 4, 5}

-- type1
local iter = list_iter(tbl)
while true do
	local element = iter()
	if not element then
		break
	end
	print(element)
end

-- type2
for element in list_iter(tbl) do
	print(element)
end

-- type3 (key的hash值排列的顺序来遍历)
for k, v in pairs(tbl) do
	print(v)
end

-- type4 (只能遍历key "为从1开始的且连接的数字" 的table，包括数组、映射表)
for k, v in ipairs(tbl) do
	print(v)
end



print("========================================")



function  myPower(x)
	return function(y) return y^x end
end

power2 = myPower(2)

print(power2(3))



tbtest = {
    [1] = 1,
    [2] = 2,
    [3] = 3,
    [4] = 4,
}
for key, value in pairs(tbtest) do
    print(value)
end