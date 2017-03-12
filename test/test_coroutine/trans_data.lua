print("========================================")
-- resume to host

print("resume -> host:")
co = coroutine.create(function(a, b, c)
	print("co", a, b, c)
end)

print(coroutine.resume(co, 1, 2, 3))
print(coroutine.status(co))


print("========================================")
-- host to resume

print("host -> resume:")
co2 = coroutine.create(function()
	return 4, 5
end)

print(coroutine.resume(co2))
print(coroutine.status(co2))



print("========================================")
-- resume to yield

print("resume -> yield:")
co3 = coroutine.create(function()
	print("co3", coroutine.yield())
end)

print(coroutine.resume(co3))	-- must in running state
print(coroutine.resume(co3, 6, 7))
print(coroutine.status(co3))



print("========================================")
-- yield to resume

print("yield -> resume:")
co4 = coroutine.create(function(a, b)
	print("co4", coroutine.yield(a+b, a-b))
end)

print(coroutine.resume(co4, 20, 10))
print(coroutine.status(co4))