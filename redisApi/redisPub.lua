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

--------------------------redis相关操作----------------------------
local redis = {}

redis.pub = function()
	local channel = KEYS[1] or "channelTmp"
	local key=KEYS[2] or "TmpDataSet"
	local retSubNum = -1 -- 数据全部pub出去瞬间的订阅人数

	local index = 0
	local run = true
	while(run)
	do
		local list = tool.getList(key, index, index+99)
		if list and next(list) then
			for k,v in pairs(list) do
				retSubNum = tool.pub(channel, v)
			end
			index = index + 100
		else
			run = false
		end
	end
	return retSubNum
end

------------------------pub一下----------------------
return redis.pub()
