local x = {1,2,3,4}
x.cc = "cc"
for k,v in pairs(x) do
	print(k,v)
end
for k,v in ipairs(x) do
	print(k,v)
end