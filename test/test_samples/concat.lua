-- table.concat
local tbl = {"a", "b", "c", "d", "e"}

-- 1������: ����ָ���������е��ֶ�
print(table.concat(tbl))

-- 2������: table, spliter
print(table.concat(tbl, "|"))

-- 3������: table, spliter, pos_start
print(table.concat(tbl, "@", 2))

-- 4������: table, spliter, pos_start, pos_end
print(table.concat(tbl, "#", 2, 4))

