-- table.concat
local tbl = {"a", "b", "c", "d", "e"}

-- 1个参数: 连接指定表中所有的字段
print(table.concat(tbl))

-- 2个参数: table, spliter
print(table.concat(tbl, "|"))

-- 3个参数: table, spliter, pos_start
print(table.concat(tbl, "@", 2))

-- 4个参数: table, spliter, pos_start, pos_end
print(table.concat(tbl, "#", 2, 4))
