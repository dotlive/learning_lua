
local strtrim = function(input)
    input = string.gsub(input, "^[ \t\n\r]+", "")
    return string.gsub(input, "[ \t\n\r]+$", "")
end
 
local strsplit = function(input, delimiter)
   if input == nil or input=="" then return {} end
   input = tostring(input)
   delimiter = tostring(delimiter)
   if (delimiter=='') then return false end
   local pos,arr = 0, {}
   -- for each divider found
   for st,sp in function() return string.find(input, delimiter, pos, true) end do
       table.insert(arr, string.sub(input, pos, st - 1))
       pos = sp + 1
   end
   table.insert(arr, string.sub(input, pos))
   return arr
end

local dump = function (value, desciption, nesting, showDumpPosition)
   if type(nesting) ~= "number" then nesting = 3 end
   if showDumpPosition == nil then showDumpPosition = true end

   local lookupTable = {}
   local result = {}

   local function _v(v)
       if type(v) == "string" then
           v = "\"" .. v .. "\""
       end
       return tostring(v)
   end

   if showDumpPosition == true then
       local traceback = strsplit(debug.traceback("", 2), "\n")
       print("dump from: " .. strtrim(traceback[3]))
   end

   local function _dump(value, desciption, indent, nest, keylen)
       desciption = desciption or "<var>"
       spc = ""
       if type(keylen) == "number" then
           spc = string.rep(" ", keylen - string.len(_v(desciption)))
       end
       if type(value) ~= "table" then
           result[#result +1 ] = string.format("%s%s%s = %s", indent, _v(desciption), spc, _v(value))
       elseif lookupTable[value] then
           result[#result +1 ] = string.format("%s%s%s = *REF*", indent, desciption, spc)
       else
           lookupTable[value] = true
           if nest > nesting then
               result[#result +1 ] = string.format("%s%s = *MAX NESTING*", indent, desciption)
           else
               result[#result +1 ] = string.format("%s%s = {", indent, _v(desciption))
               local indent2 = indent.."    "
               local keys = {}
               local keylen = 0
               local values = {}
               for k, v in pairs(value) do
                   keys[#keys + 1] = k
                   local vk = _v(k)
                   local vkl = string.len(vk)
                   if vkl > keylen then keylen = vkl end
                   values[k] = v
               end
               table.sort(keys, function(a, b)
                   if type(a) == "number" and type(b) == "number" then
                       return a < b
                   else
                       return tostring(a) < tostring(b)
                   end
               end)
               for i, k in ipairs(keys) do
                   _dump(values[k], k, indent2, nest + 1, keylen)
               end
               result[#result +1] = string.format("%s}", indent)
           end
       end
   end
   _dump(value, desciption, "- ", 1)

   for i, line in ipairs(result) do
       print(line)
   end
end

return
{
    strtrim = strtrim,
    strsplit = strsplit,
    dump = dump,
}
