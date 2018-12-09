co = coroutine.create(function()
	print "hi"
end)

print(co)

print(coroutine.status(co))  	-- suspended
coroutine.resume(co)			-- running
print(coroutine.status(co))		-- dead


print("========================================")


co2 = coroutine.create(function()
	for i=1, 5 do
		print("co2", i)
		coroutine.yield()
	end
end)

coroutine.resume(co2)
print(coroutine.status(co2))
coroutine.resume(co2)
print(coroutine.status(co2))
coroutine.resume(co2)
print(coroutine.status(co2))
coroutine.resume(co2)
print(coroutine.status(co2))
coroutine.resume(co2)
print(coroutine.status(co2))

-- run in safe mode, so no error throws
coroutine.resume(co2)
print(coroutine.status(co2))

print(coroutine.resume(co2))