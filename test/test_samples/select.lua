--[[
	select(index, ...) -- 处理不定参用
	1. index 为数字时, 输出从index开始的所有剩余参数; -1表示最后一个
	2. index 为 '#' 时, 输出可变参数总数
--]]

local f = function(a, b, ...)
	print("non-extra:")
	print(a)
	print(b)

	local count = select('#', ...)

	print("traverse_1:")
	for i = 1, count do
		print(select(i, ...))
	end

	print("traverse_2:")
	for i = 1, count do
		local arg = select(i, ...)
		print(arg)
	end
end

f(1, 2, 'a', 'b', 'c')

