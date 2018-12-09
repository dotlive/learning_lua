#!/usr/local/bin/lua

--[[

-- test.001 输出语句测试
print("Hello World")

--]]


--[[

-- test.002 函数测试
local function fact(n)
    if n == 0 then
        return 1
    else
        return n * fact(n-1)
    end
end

--print("Please enter a number:")
--a = io.read("*n")
print(fact(5))

--]]


--[[

-- test.003
--乘方
print(2^3)

--]]


-- test.004 table相关特性测试
--[[
	结论：
	1. table既可以当array/list用，也可以当record用，而且还可以混用。但table貌似是用map来实现的，array是语法糖，一种特例，array的key就是它的数组索引；
	2. 遍历。当array用的时候，虽然不用写key了，但当索引不连续的时候，用#获取的长度就会有问题，此时获取长度也没意义了。所以当数组元素被删除的时候，要特别注意；
--]]

-- 长度相关测试：置空的时候，跟索引是奇数还是偶数，结果不一致
--[[
t0 = {}

for i = 1, 99 do t0[i] = i * 2 end
print(#t0)

local index = 97
t0[index] = nil
print(t0[index])
print(#t0)

t00 = {1, 2, 3}
print(#t00)

t000 = {1, 2, 3,}
print(#t000)

t01 = {1, nil}
print(#t01)

t02 = {1, nil, 2}
print(#t02)

t03 = {1, nil, 2, nil}
print(#t03)

t04 = {1, nil, 2, nil, 3}
print(#t04)

--print(table.maxn(t))
--]]

-- 下标从1开始
--[[
t1 = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}
print(t1[0])
print(t1[1])
--]]

-- record
--[[
t2 = {
	name = "gyy",		-- 这种写法，只是字符串做为Key的一种语法糖而已。下面的写法才是正统的写法
	["name"] = "gyy1",
	[-1] = 2,
}
print(t2.name)
print(t2[name])
print(t2["name"])
print(t2[-1])
--]]

-- traverse
--[[
t3 = {1, 2, 3}
--t3[4] = 4
t3[5] = 5
for i=1, #t3 do
	print(t3[i])
end

--for k, v in pairs(_G) do print(k, v) end

t4 = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}
t5 = {}
for k, v in ipairs(t4) do
	t5[v] = k
end
print(t5.Monday)
--]]


--[[

-- test.005 Iterator
function List_Iter(list)
	local index = 0
	local count = #list
	return function()
		index = index + 1
		if index <= count then return list[index] end
	end
end

t = {1,2,3,5}
iter = List_Iter(t)
while true do
	local value = iter()
	if not value then break end
	print(value)
end

--]]


--[[

-- test.006
f = loadstring("i = i + 1")
i = 0
f()	print(i)
f()	print(i)
f()	print(i)

--]]


-- test.007 coroutine
---[[

-- look up all members of coroutine
--for k, v in pairs(coroutine) do print(k, v) end

-- basic
--[[
co = coroutine.create(function() print("hi") end)
print(co)

print(coroutine.status(co))

coroutine.resume(co)
print(coroutine.status(co))
--]]

-- resume
--[[
co1 = coroutine.create(
	function()
		for i = 1, 10 do
			print(i)
			coroutine.yield()
		end
	end
)

function test_co1()
	coroutine.resume(co1)
	print(coroutine.status(co1))
end

test_co1()
test_co1()
test_co1()
test_co1()
test_co1()
test_co1()
test_co1()
test_co1()
test_co1()
test_co1()
test_co1()
print(coroutine.resume(co1))
--]]

-- resume-yield交换数据
--[[
co2 = coroutine.create(
	function(a, b, c)
		print("co2", a, b, c)
	end
)
coroutine.resume(co2, 1,2,3)

co3 = coroutine.create(
	function(a, b)
		coroutine.yield("co3", a + b, a - b)
	end
)
print("1 ", coroutine.resume(co3, 10, 20))
print("2 ", coroutine.resume(co3, "10", 20))

--]]

--]]


--[[

-- test.008 metatable
-- __index : 访问
-- ——newindex : 修改
t = {}
print(getmetatable(t))

t1 = {}
print(t1)
setmetatable(t, t1)
print(#getmetatable(t))

function setDefault(t, d)
	local mt = {__index = function() return d end}
	setmetatable(t, mt)
end
setDefault(t1, 100)
print(t1.x)
print(t1.y)
print(t1.z)
--]]


-- test.009 oop
--[[
Account = { name = "", balance = 0 }

function Account:new(name, balance)
	o = {}
	setmetatable(o, self)
	self.__index = self
	o.name = name
	o.balance = balance
	return o
end

function Account:withdraw(v)
	self.balance = self.balance - v
end

function Account:diposit(v)
	self.balance = self.balance + v
end

function Account:display()
	print(self.name, self.balance)
end

-- : 只是用来隐藏self，或者this参数
--Account:withdraw(10)

a1 = Account:new("gyy1", 10)
a1:display()  -- <==> a1.display(a1)
a2 = Account:new("gyy2", 20)
a1:display()
a2:display()
a3 = Account:new("gyy3", 30)
a1:display()
a2:display()
a3:display()

--]]


-- test.010 weak table
---[[
a = {}
setmetatable(a, {__mode='kv'}) --k,v,kv

a.x = 0

key = {}
a[key] = 1

key = {}
a[key] = 2

collectgarbage()
for _, v in pairs(a) do
	print(v)
end

--note:只有拥有显示构造的对象类型会被自动从weak表中移除，值类型boolean、number是不会自动从weak中移除的。而string类型虽然也由gc来负责清理，但是string没有显示的构造过程，因此也不会自动从weak表中移除，对于string的内存管理有单独的策略。

--]]



