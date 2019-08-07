local tool = {}
--
tool.debug = function(debugStr)
	local strType = type(debugStr)
	if strType == "nil" then
		debugStr = strType
	elseif strType == "boolean" then
		debugStr = debugStr and "true" or "false"
	end

	local str = "[redis lua]:"
	local timeInfo = redis.call("time")
	-- print(timeInfo[1].."-"..timeInfo[2]..str..debugStr)
	redis.log(redis.LOG_NOTICE,str..timeInfo[1].."-"..timeInfo[2]..":"..debugStr)
end

tool.xsub = function(key, message)
	if not key or not message then return end

	local data = redis.call("xread","block","0","streams",key,"$")
	return data
end

--------------------------redis相关操作----------------------------
local redis = {}

redis.xsub = function()
	local channel = KEYS[1] or "memberTmp"
	local data = "no data"
	data = tool.xsub(channel)
	return data 
end

------------------------pub一下----------------------
return redis.xsub()
