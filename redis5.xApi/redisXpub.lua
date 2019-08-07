local tool = {}

tool.pub = function(channel, message)
	if not channel or not message then return end

	local subNum = redis.call("publish",channel,message)
	return subNum
end

tool.getList = function(key, from, to)
	if not key or not from or not to then return end

	local retList = redis.call("lrange",key,from,to)
	return retList
end

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

tool.xpub = function(key, message)
	if not key or not message then return end

	local messageId = redis.call("xadd",key,"maxlen","1000","*","message",message)
	return messageId
end

--------------------------redis相关操作----------------------------
local redis = {}

redis.xpub = function()
	local channel = KEYS[1] or "memberTmp"
	local key=ARGV[1] or "TmpDataSet"
	local messageId = "no messageId"

	local index = 0
	local run = true
	tool.debug("we start xpub")
	while(run)
	do
		local list = tool.getList(key, index, index+99)
		if list and next(list) then
			for k,v in pairs(list) do
				messageId = tool.xpub(channel, v)
			end
			index = index + 100
		else
			run = false
		end
	end
	tool.debug("xpub finish")
	return messageId
end

------------------------pub一下----------------------
return redis.xpub()
