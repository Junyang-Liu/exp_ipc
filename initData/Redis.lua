local tool = {}
tool.random = function(n, m)
    math.randomseed(math.random(1000000,90000000)+math.random(1000000,90000000))
    return math.random(n, m)
end

tool.randomLetter = function(len)
    local rt = ""
    for i = 1, len, 1 do
        rt = rt..string.char(tool.random(97,122))
    end
    return rt
end

table.tostring = function(data, _indent)
	local visited = {}
	local function dump(data, prefix)
		local str = tostring(data)
		if table.find(visited, data) ~= nil then return str end
		table.insert(visited, data)

		local prefix_next = prefix .. "  "
		str = str .. "\n" .. prefix .. "{"
		for k,v in pairs(data) do
			if type(k) == "number" then
				str = str .. "\n" .. prefix_next .. "[" .. tostring(k) .. "] = "
			else
				str = str .. "\n" .. prefix_next .. tostring(k) .. " = "
			end
			if type(v) == "table" then
				str = str .. dump(v, prefix_next)
			elseif type(v) == "string" then
				str = str .. '"' .. v .. '"'
			else
				str = str .. tostring(v)
			end
		end
		str = str .. "\n" .. prefix .. "}"
		return str
	end
	return dump(data, _indent or "")
end

-- http://snippets.luacode.org/?p=snippets/Deep_copy_of_a_Lua_Table_2
table.clone = function(t,deepnum)
	if type(t) ~= 'table' then return t end
	local mt = getmetatable(t)
	local res = {}

	if deepnum and deepnum > 0 then
		deepnum = deepnum - 1
	end
	for k,v in pairs(t) do
		if type(v) == 'table' then
			if not deepnum or deepnum > 0 then
				v = table.clone(v, deepnum)
			end
		end
		res[k] = v
	end
	setmetatable(res,mt)
	return res
end

--------------------------redis相关操作----------------------------

local key=KEYS[1] or "TmpDataSet"
local num = KEYS[2] or 5000
local list = nil

for i=1,num do
	list=redis.call("lpush",key,tool.randomLetter(500))
end

return list
