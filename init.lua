package.path = package.path .. ";./utils/?.lua"
package.path = package.path .. ";./test/?.lua"

require("test.init")
