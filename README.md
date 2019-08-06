# Exp_IPC

IPC demo

目录说明:
	./shm (Linux 共享内存)
		使用sys/shm.h库实现共享内存

	./boostApi (interprocess 共享内存)
		使用managed_shared_memory实现共享内存

	./initData (初始化redis数据库,生成随机数据所用的脚本工具)
		Redis.lua 脚本生成一点(5000条)长500个字符的字符串,调用Redis接口,lpush到Redis list
		RedisRead.lua 脚本调用Redis接口lrange 10条Redis list 的数据
		RedisApi.cpp 使用hiredis调用Redis接口,lrange 数据

	./redisApi (redis pub/sub模式)
		redisPub.lua 脚本调用Redis接口,把一个list的所有数据publish到一个channel,统计Redis pub/sub模式数据开始发布到数据发布完的时间
		redisSub.cpp 使用hiredis调用Redis接口,subscribe一个channel,统计Redis pub/sub模式数据开始订阅到数据接收完的时间

	./zmqApi (zmq pub/sub模式)
		client.cpp && server.cpp 使用zmq实现 请求/回复
		psenvpub.cpp && psenvsub.cpp 使用zmq 实现 pub/sub模式

	./zmqApi/zmq_pb_redisdb (zmq pub/sub模式,使用hiredis读取数据,zmq发布)
		psenvpub.cpp && psenvsub.cpp zmq pub/sub模式发数据,统计发布开始发布结束,开始接收数据到结束的时间


具体实现效果:

Redis 存个80000条随机字符:

![Image text](https://s2.ax1x.com/2019/08/06/e48HGd.png)


Redis pub/sub:

	pub运行:

![Image text](https://s2.ax1x.com/2019/08/06/e48oIe.png)


	sub运行:

![Image text](https://s2.ax1x.com/2019/08/06/e487PH.png)


zmq pub/sub:
	先起sub:

![Image text](https://s2.ax1x.com/2019/08/06/e48IaD.png)

	
	起pub:

![Image text](https://s2.ax1x.com/2019/08/06/e48bRA.png)


	sub显示:

![Image text](https://s2.ax1x.com/2019/08/06/e48OMt.png)


