--------------------------redis相关操作----------------------------

local key=KEYS[1] or "TmpDataSet"
local num = KEYS[2] or 5000

local list=redis.call("lrange",key,0,10)

return list