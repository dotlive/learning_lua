--[[
    desc:
        文件系统, 主要封装对文件和目录的操作接口
    author:
        gongyy
--]]

local lfs = require("lfs")
local util = require("utils.util")

--------------------------------------------------------------------------------------
-- internal functions

local path_attr = function(path)
    if not path then
        return nil
    end
    return lfs.attributes(path)
end

--------------------------------------------------------------------------------------
-- for directory operations

local is_dir = function(dir)
    local attr = path_attr(dir)
    if attr and attr.mode == "directory" then
        return true
    end
    return false
end

local exist_dir = function(dir)
    return is_dir(dir)
end

local parent_dir = function(input, target)
    local temp = input:gsub("\\", "/")
    local rtemp = temp:reverse()
    local pos = rtemp:find("/")
    return temp:sub(0, temp:len() - pos)
end

local create_dir = function(dir, is_file)
    local temp_dir = dir
    if is_file then
        temp_dir = parent_dir(temp_dir)
    end
    print(temp_dir)
    if exist_dir(temp_dir) then
        return
    end
    local normalized_dir = string.gsub(temp_dir, "\\", "/")
    --print(normalized_dir)
    local child_dirs = util.strsplit(normalized_dir, "/")
    local temp_fulldir = ""
    for i = 1, #child_dirs do
        if temp_fulldir ~= "" then
            temp_fulldir = temp_fulldir .. "/"
        end
        local child_dir = child_dirs[i]
        temp_fulldir = temp_fulldir .. child_dir
        if child_dir ~= "." and child_dir ~= ".." then
            if not exist_dir(temp_fulldir) then
                lfs.mkdir(temp_fulldir)
            end
        end
    end
end

--------------------------------------------------------------------------------------
-- for file operations

local getfilelist = function(dir, filelist)
    assert(filelist ~= nil)
    if not filelist then
        return
    end
    for entry in lfs.dir(dir) do
        if entry ~= '.' and entry ~= '..' then
            local path = dir .. "\\" .. entry
            local attr = lfs.attributes(path)
            assert(type(attr) == "table")
            if(attr.mode == "directory") then
                getfilelist(path, filelist)
            elseif attr.mode=="file" then
                --print(attr.mode, path)
                table.insert(filelist, path)
            end
        end
    end
end

local is_file = function(path)
    local attr = path_attr(path)
    if attr and attr.mode == "file" then
        return true
    end
    return false
end

local exist_file = function(path)
    return is_file(path)
end

local readfile = function(path, mode)
    mode = mode or "r"
    local file = io.open(path, mode)
    if not file then
        return nil
    end
    local content = file:read("*a")
    io.close(file)
    return content
end

local writefile = function(path, content, mode)
    mode = mode or "w+b"
    local file = io.open(path, mode)
    if not file then
        return false
    end
    local ret = file:write(content)
    if not ret then
        return false
    end
    return true
end

-- export
return
{
    -- for dir
    is_dir = is_dir,
    exist_dir = exist_dir,
    create_dir = create_dir,
    -- for files
    getfilelist = getfilelist,
    is_file = is_file,
    exist_file = exist_file,
    readfile = readfile,
    writefile = writefile,
}
