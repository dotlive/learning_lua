--require("a.b.target")

local luafs = require("lfs")

local allFilePath = {}

local get_all_files = function (rootpath)
    for entry in lfs.dir(rootpath) do
        if entry ~= '.' and entry ~= '..' then
            local path = rootpath .. "\\" .. entry
            local attr = lfs.attributes(path)
            assert(type(attr) == "table") --如果获取不到属性表则报错
            -- PrintTable(attr)
            if(attr.mode == "directory") then
                -- print("Dir:",path)
                get_all_files(path) --自调用遍历子目录
            elseif attr.mode=="file" then
                -- print(attr.mode,path)
                table.insert(allFilePath,path)
            end
        end
    end
end

get_all_files("../../data/cpp")
print(#allFilePath)
