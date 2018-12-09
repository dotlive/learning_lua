print("run in lua....")

print(global_cpp)

--[[
for i = 1, #arg do
    print(arg[i])
end
--]]

local pairsByKeys = function(t)  
    local a = {}  
    for n in pairs(t) do  
        a[#a+1] = n  
    end  
    table.sort(a)  
    local i = 0  
    return function()  
        i = i + 1  
        return a[i], t[a[i]]  
    end  
end 

for key, value in pairsByKeys(arg) do  
    print(key .. " " .. value)
end