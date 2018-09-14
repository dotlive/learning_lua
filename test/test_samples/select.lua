--[[
	select(index, ...) -- ����������
	1. index Ϊ����ʱ, �����index��ʼ������ʣ�����; -1��ʾ���һ��
	2. index Ϊ '#' ʱ, ����ɱ��������

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

